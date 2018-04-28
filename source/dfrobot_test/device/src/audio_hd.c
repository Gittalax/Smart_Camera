#include "common.h"
#include "pcm_lib.h"
#include "audio_hd.h"

/**
 * NAME         audio_da_open
 * @BRIEF	�� DA
                  
 * @PARAM	T_AUDIO_INPUT *input����ʱ���õĲ���
                    
 * @RETURN	void *
 * @RETVAL	ָ��򿪺�ľ��
 */

void * audio_da_open(T_AUDIO_INPUT *input)
{
    void *handle;
    pcm_pars_t da_info;
    handle = pcm_open(PCM_DEV_DA);

    da_info.samplebits = input->nBitsPerSample;
    da_info.samplerate = input->nSampleRate;
    pcm_ioctl(handle, DA_SET_PARS, (void *)&da_info);
    return handle;
}


/**
 * NAME         audio_da_filter_enable
 * @BRIEF	����DA �ز���
                  
 * @PARAM	void *handle,��ʱ���صľ��
 			int enable,	1������0����
                    
 * @RETURN	void 
 * @RETVAL	
 */

void audio_da_filter_enable(void *handle, int enable)
{
    pcm_ioctl(handle, DA_SET_SDF, (void *)&enable);
}

/**
 * NAME         audio_da_spk_enable
 * @BRIEF	����DA pa
                  
 * @PARAM	
 			int enable,	1������0����
 * @RETURN	void 
 * @RETVAL	
 */

void audio_da_spk_enable(int enable)
{
    pcm_set_speaker_enable(enable);	
}

/**
 * NAME         audio_write_da
 * @BRIEF	дDA
                  
 * @PARAM	void *handle,  ��ʱ���صľ�� 
 			uint8 *pdata,  Ҫд������
 			int buf_size,    ���ݵĴ�С
 			
 * @RETURN	int 
 * @RETVAL	ʵ��д��DA �����ݴ�С
 */

int audio_write_da(void *handle, uint8 *pdata, int buf_size)
{
    return pcm_write(handle, pdata, buf_size);
}


/**
 * NAME         audio_da_close
 * @BRIEF	�ر�DA
                  
 * @PARAM	void *handle,  ��ʱ���صľ�� 

 * @RETURN	int 
 * @RETVAL	 if return 0 success, otherwise failed
 */

int audio_da_close(void *handle)
{
	return pcm_close(handle);
}

/**
 * NAME         audio_da_open
 * @BRIEF	�� AD
                  
 * @PARAM	T_AUDIO_INPUT *input����ʱ���õĲ���
                    
 * @RETURN	void *
 * @RETVAL	ָ��򿪺�ľ��
 */
void *audio_ad_open(T_AUDIO_INPUT *input)
{
    void *handle;
    pcm_pars_t da_info;
    handle = pcm_open(PCM_DEV_AD);

    da_info.samplebits = input->nBitsPerSample;
    da_info.samplerate = input->nSampleRate;
    pcm_ioctl(handle, AD_SET_PARS, (void *)&da_info);    
    return handle;
}


/**
 * NAME         audio_ad_filter_enable
 * @BRIEF	����AD �ز���
                  
 * @PARAM	void *handle,��ʱ���صľ��
 			int enable,	1������0����
                    
 * @RETURN	void 
 * @RETVAL	
 */

void audio_ad_filter_enable(void *handle, int enable)
{
    pcm_ioctl(handle, AD_SET_SDF, (void *)&enable);
}

/**
 * NAME        audio_ad_clr_buffer
 * @BRIEF	���AD ������BUF
                  
 * @PARAM	void *handle,��ʱ���صľ��
 * @RETURN	void 
 * @RETVAL	
 */
void audio_ad_clr_buffer(void *handle)
{
    pcm_ioctl(handle, SET_RSTBUF, (void *)~0);
}


/**
 * NAME        audio_da_clr_buffer
 * @BRIEF	���DA ������BUF
                  
 * @PARAM	void *handle,��ʱ���صľ��
 * @RETURN	void 
 * @RETVAL	
 */

void audio_da_clr_buffer(void *handle)
{
    pcm_ioctl(handle, SET_RSTBUF, (void *)~0);
}

/**
 * NAME        audio_set_smaple
 * @BRIEF	����ad ������
                  
 * @PARAM	void *handle,��ʱ���صľ��
			T_AUDIO_INPUT *input, ָ�����ָ��
 * @RETURN	void 
 * @RETVAL	
 */

void audio_set_smaple(void *handle, T_AUDIO_INPUT *input)
{
    pcm_pars_t ad_info;
 
    ad_info.samplebits = input->nBitsPerSample;
    ad_info.samplerate = input->nSampleRate;
    pcm_ioctl(handle, AD_SET_PARS, (void *)&ad_info);
}

/**
 * NAME        audio_set_mic_vol
 * @BRIEF	����ad ��������
                  
 * @PARAM	void *handle,��ʱ���صľ��
			 int vol��Ҫ���õ�����
 * @RETURN	void 
 * @RETVAL	
 */

/*
  * vol: 0~7, ��ֵԽ������Խ��
*/
void audio_set_mic_vol(void *handle, int vol)
{
    pcm_ioctl(handle, AD_SET_GAIN, (void *)&vol);
}


/**
 * NAME        audio_set_da_vol
 * @BRIEF	����DA  ��������
                  
 * @PARAM	void *handle,��ʱ���صľ��
			 int vol��Ҫ���õ�����
 * @RETURN	void 
 * @RETVAL	
 */
/*
  * vol: 0~5, ��ֵԽ������Խ��
*/
void audio_set_da_vol(void *handle, int vol)
{
    pcm_ioctl(handle, DA_SET_GAIN, (void *)&vol);
}

/**
 * NAME        audio_read_ad
 * @BRIEF	��AD ����������
                  
 * @PARAM	void *handle,��ʱ���صľ��
			uint8 *pdata, ���ݴ�ŵ�ַ
			int buf_size, Ҫ����size
			unsigned long *ts, ʱ���
 * @RETURN	int  
 * @RETVAL	if return 0 success, otherwise failed
 */
int audio_read_ad(void *handle, uint8 *pdata, int buf_size, unsigned long *ts)
{
	int ret;
    
    ret = pcm_read(handle, pdata, buf_size);
	
	pcm_get_timer(handle, ts);

	return ret;
}

/**
 * NAME        audio_ad_close
 * @BRIEF	�ر�AD
                  
 * @PARAM	void *handle,��ʱ���صľ��

 * @RETURN	int  
 * @RETVAL	if return 0 success, otherwise failed
 */

int audio_ad_close(void *handle)
{
	return pcm_close(handle);
}


/**
 * NAME        audio_set_ad_agc_enable
 * @BRIEF	AD agc �Զ�������ƿ���
                  
 * @PARAM	int enable,	1������0����
 * @RETURN	int  
 * @RETVAL	if return 0 success, otherwise failed
 */

int audio_set_ad_agc_enable(int enable)
{
	return pcm_set_nr_agc_enable(PCM_DEV_AD, enable);
}

/**
 * NAME        audio_set_da_agc_enable
 * @BRIEF	DA agc �Զ�������ƿ���
                  
 * @PARAM	int enable,	1������0����
 * @RETURN	int  
 * @RETVAL	if return 0 success, otherwise failed
 */

int audio_set_da_agc_enable(int enable)
{
    return 0;
	return pcm_set_nr_agc_enable(PCM_DEV_DA, enable);
}

/**
 * NAME        audio_get_ad_status
 * @BRIEF	��ȡAD ״̬
                  
 * @PARAM	int enable,	1������0����
 * @RETURN	int  
 * @RETVAL	if return 0 success, otherwise failed
 */

int audio_get_ad_status(void)
{
	return pcm_get_status(PCM_DEV_AD);
}


/**
 * NAME        audio_get_da_status
 * @BRIEF	��ȡDA ״̬
                  
 * @PARAM	void
 * @RETURN	int  
 * @RETVAL	if return 0 don't working, otherwise working.
 */
int audio_get_da_status(void)
{
	return pcm_get_status(PCM_DEV_DA);
}


