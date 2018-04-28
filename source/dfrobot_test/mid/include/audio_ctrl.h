#ifndef _audio_ctrl_h_
#define _audio_ctrl_h_
#define AUDIO_INFORM_LENGTH (8)

#ifdef	CHIP_ID_AK37XX
#include <akmedialib/sdfilter.h>
#endif
#include <audio_enc.h>
#include <pthread.h>
#include "audio_enc.h"
#include "video_ctrl.h"

#ifdef __cplusplus  //jwy add 2016.05.31
extern "C" {
#endif


typedef struct {
	T_U32		nSampleRate;
	T_U32		nBitsPerSample;
	T_U32		nChannels;
}T_AUDIO_INPUT;



typedef struct {
	T_BOOL		bIsStop;
	T_U32		nGetPacketNum;
	T_U32		nPeriodDuration;
	T_U32		nOnceBufSize;

	T_U32		nSampleRate;
	T_U32		nBitsPerSample;
	T_U32		nChannels;
	T_U32		nBitsRate;
	AUDIO_ENCODE_TYPE_CC enc_type;
}T_AUDIO_READ;

enum
{
    SYS_AUDIO_ENCODE_AAC,
    SYS_AUDIO_ENCODE_G711,
    SYS_AUDIO_ENCODE_AMR,
    SYS_AUDIO_RAW_PCM,
    SYS_AUDIO_ENCODE_MAX,
        
};

#define AUDIO_QUEUE_MAX_ITEM 500

struct _audio_user_thread_handle_;

typedef void AUDIO_SEND_CALLBACK(void *param, T_STM_STRUCT *pstream);

typedef struct _audio_user_thread_handle_
{
    uint8        run_flag;
    void        *param;
    void        *queue_handle;
    sem_t     audio_data_sem;
    PA_HTHREAD      send_handle;    
    AUDIO_SEND_CALLBACK *callback;
    struct _audio_user_thread_handle_ *next;
}audio_user_thread_handle, *Paudio_user_thread_handle;

typedef struct _audio_pcm_queue_data
{
    int     pcm_size;
    uint8 * pcm_buffer;
}audio_pcm_queue_data, *Paudio_pcm_queue_data;

struct _audio_encode_data_info;
typedef struct _audio_encode_data_info
{
    int     working_flag;
    void    *encode_handle;
    pthread_mutex_t     audio_ctrl_mutex;
    Paudio_user_thread_handle audio_user_handle;
}audio_encode_data_info, *Paudio_encode_data_info;




typedef struct _audio_ctrl_handle
{    
    int     encode_size;
    uint8   *encode_buffer;
    T_AUDIO_READ    gaudio;
    PA_HTHREAD      pcm_thread;    
    sem_t           audio_ad_sem;
    void    *ad_handle;
    audio_encode_data_info encode_queue_info[SYS_AUDIO_ENCODE_MAX];
 } audio_ctrl_handle, *Paudio_ctrl_handle;

/**
 * NAME         audio_add
 * @BRIEF	Ӧ��������Ƶһ��ʵ����Ŀǰ֧�����¼��ֱ��뷽ʽ��SYS_AUDIO_ENCODE_AAC,SYS_AUDIO_ENCODE_G711,SYS_AUDIO_RAW_PCM,
 * @PARAM	encode_type   ��Ӧ��Ҫ����ı����ʽ
                    pcallback �ɼ������ݵĻص�����
                    mydata    �ص��ش���Ӧ�õ�����ָ��
 * @RETURN	-1-->fail; 0-->ok
 * @RETVAL	
 */

int audio_add(int  encode_type, AUDIO_SEND_CALLBACK *pcallback, void *mydata);

/**
 * NAME         audio_del
 * @BRIEF	Ӧ��ֹͣ��Ƶ��ʹ�ã����ͷ�Ϊ���������Դ
 * @PARAM	encode_type   ��Ӧ��Ҫ����ı����ʽ
                    mydata    �ص��ش���Ӧ�õ�����ָ��
 * @RETURN	NONE
 * @RETVAL	
 */

void audio_del(int  encode_type, void *mydata);

/**
 * NAME         audio_start
 * @BRIEF	 ������Ƶ
 * @PARAM	input
 * @RETURN	void
 * @RETVAL	
 */


int audio_start(T_AUDIO_INPUT *input);

/**
 * NAME         audio_modify_sample
 * @BRIEF	 �޸Ĳ�����
 * @PARAM	input
 * @RETURN	void
 * @RETVAL	
 */
void audio_modify_sample(T_AUDIO_INPUT *input);

/**
 * NAME         audio_modify_vol
 * @BRIEF	 �޸�gain
 * @PARAM	vol, ���ֵ ԽС������Խ��
 * @RETURN	void
 * @RETVAL	
 */

void audio_modify_vol(int vol);


/**
 * NAME         audio_modify_filter
 * @BRIEF	 �ز����Ŀ��أ�
 * @PARAM	on_off
 * @RETURN	void
 * @RETVAL	
 */

void audio_modify_filter(int on_off);


#ifdef __cplusplus  //jwy add 2016.05.31
} /* end extern "C" */
#endif


#endif


