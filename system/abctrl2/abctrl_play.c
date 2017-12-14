#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>
#include <qsdk/audiobox2.h>
#include <qsdk/event.h>
#include "abctrl.h"

static int safe_read(int fd, void *buf, size_t count)
{
	int result = 0, res;

	while (count > 0) {
		if ((res = read(fd, buf, count)) == 0) 
			break;
		if (res < 0)
			return result > 0 ? result : res;
		count -= res;
		result += res;
		buf = (char *)buf + res;
	}

	return result;
}

static int get_frame_size(audio_fmt_t *fmt)
{
	int bitwidth;

	if (!fmt)
		return -1;
	
	bitwidth = ((fmt->bitwidth > 16) ? 32 : fmt->bitwidth);
	return (fmt->channels * (bitwidth >> 3));
}

int playback(int argc, char **argv)
{
	int option_index;
	char const short_options[] = "c:v:d:w:s:n:t:p:";
	struct option long_options[] = {
		{ "channel", 0, NULL, 'c' },
		{ "volume", 0, NULL, 'v' },
		{ "input", 0, NULL, 'd' },
		{ "bit-width", 0, NULL, 'w' },
		{ "sample-rate", 0, NULL, 's' },
		{ "channel-count", 0, NULL, 'n' },
		{ "count", 0, NULL, 't'},
		{ "priority", 0, NULL, 'p'},
		{ 0, 0, 0, 0 },
	};
	int ch, ret, volume = 100;
	int count = 1;
	int priority = 0;
	int handle, len, fd;
	char pcm_name[32] = "default";
	char *wavfile = NULL;
	char *audiobuf = NULL;
	audio_fmt_t fmt = {
		.channels = 2,
		.bitwidth = 32,
		.samplingrate = 48000,
		.sample_size = 1024,
	};
	int length;
		
	while ((ch = getopt_long(argc, argv, short_options,
					long_options, &option_index)) != -1) {
		switch (ch) {
			case 'c':
				sprintf(pcm_name, "%s", optarg);
				break;
			case 'v':
				volume = strtol(optarg, NULL, 0);
				break;
			case 'd':
				wavfile = optarg;
				break;
			case 'w':
				fmt.bitwidth = strtol(optarg, NULL, 0);
				break;
			case 's':
				fmt.samplingrate = strtol(optarg, NULL, 0);
				break;
			case 'n':
				fmt.channels = strtol(optarg, NULL, 0);
				break;
			case 't':
				count = strtol(optarg, NULL, 0);
				break;
			case 'p':
				priority = strtol(optarg, NULL, 0);
				break;
			default:
				ABCTL_ERR("Try `ctrlab --help' for more information.\n");
				return -1;
		}
	};

	audio_set_format(pcm_name, &fmt);
	
	ABCTL_DBG(
		   ("pcm_name: %s\n"
			"volume: %d\n"
			"wavfile: %s\n"
			"fmt.codec_type: %d\n"
			"fmt.bitwidth: %d\n"
			"fmt.samplingrate: %d\n"
			"fmt.channels: %d\n"),
			pcm_name, volume, wavfile, fmt.codec_type, fmt.bitwidth, fmt.samplingrate, fmt.channels);

	while (count) {
		handle = audio_get_channel(pcm_name, &fmt, priority ? CHANNEL_FOREGROUND : CHANNEL_BACKGROUND);
		if (handle < 0) {
			ABCTL_ERR("Get channel err: %d\n", handle);
			return -1;
		}

		ret = audio_get_master_volume(pcm_name);
		if (ret < 0) {
			ABCTL_ERR("Get volume err: %d\n", ret);
			return -1;
		}

		ABCTL_ERR("Get volume: %d\n", ret);
		if (ret != volume) {
			ret = audio_set_master_volume(pcm_name, volume);
			if (ret < 0) {
				ABCTL_ERR("Set volume err: %d\n", ret);
				return -1;
			}
			ABCTL_ERR("Set volume: %d\n", volume);
		}

		ret = audio_get_chn_fmt(handle, &fmt);
		if (ret < 0) {
			ABCTL_ERR("Get format err: %d\n", ret);
			audio_put_channel(handle);
			return -1;
		}

		if (wavfile) {
			fd = open(wavfile, O_RDONLY);
			if (fd < 0) {
				ABCTL_ERR("Please Input right wav file path: %d\n", fd);
				audio_put_channel(handle);
				return -1;
			}
		} else
			fd = fileno(stdin);

		length = get_frame_size(&fmt) * fmt.sample_size;
		audiobuf = (char*)malloc(length);
		if(NULL == audiobuf) {
			ABCTL_ERR("audiobuf malloc failed!!\n");
			close(fd);
			audio_put_channel(handle);
			return -1;
		}

		do {
			len = safe_read(fd, audiobuf, length);
			if (len < 0) {
				ABCTL_ERR("safe_read err: %d\n", len);
				break;
			}

			ret = audio_write_frame(handle, audiobuf, len);
			if (ret < 0){                               
				ABCTL_ERR("audio_write_frame err: %d\n", ret);
				break;                                 
			}
			//ABCTL_ERR("len: %d, length = %d\n", len, length);
		} while (len == length);

		if (wavfile)
			close(fd);
		free(audiobuf);
		
		audio_put_channel(handle);
		usleep(10000);
		count--;
	}

	return 0;
}


