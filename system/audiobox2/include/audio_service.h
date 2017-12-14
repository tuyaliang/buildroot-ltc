#ifndef __AUDIO_SERVICE_H__
#define __AUDIO_SERVICE_H__

enum PBMODE {
	AUD_SINGLE_STREAM,
	AUD_MIXER_STREAM,
	AUD_MIXER_VOL_STREAM,
};

extern int audio_create_chnserv(audio_dev_t dev);
extern void audio_release_chnserv(audio_dev_t dev);
extern int audiobox_inner_put_channel(audio_chn_t chn);

#endif
