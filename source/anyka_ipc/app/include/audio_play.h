#ifndef _AUDIO_PLAY_H_
#define _AUDIO_PLAY_H_

/**
 * NAME         audio_play_start
 * @BRIEF	��ʼAMR�����ֲ��ţ�Ŀǰֻ����AMR�ļ��Ĳ���
 * @PARAM	audio_path   AMR����·��
                    del_flag �Ƿ�ɾ���ļ�
 * @RETURN	NONE
 * @RETVAL	
 */


void audio_play_start(char *audio_path, int del_flag);


/**
 * NAME         audio_play_stop
 * @BRIEF	ֹͣ��ǰ���ֵĲ���
 * @PARAM	void
 * @RETURN	NONE
 * @RETVAL	
 */

void audio_play_stop(void);

#endif

