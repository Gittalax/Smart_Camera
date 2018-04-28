/*******************************************************************
���ļ����������Ƶ��������ֹͣ����ͼƬ�ķ���
*******************************************************************/

#include "common.h"
#include "dana_interface.h"

#define HIGH_BPS 100
#define NORMAL_BPS 60
#define BPS_DIVIDE 25	//���ʷָ�ֵ



/**
 * NAME         anyka_stop_video
 * @BRIEF	��������Ƶ�������޸�������Ƶ����
 * @PARAM	mydata           �û����ݣ��˽ṹ��ָ��Ҫ��anyka_start_video����һ��
 * @RETURN	void
 * @RETVAL	
 */

void anyka_stop_video(void *mydata)
{
    video_del(mydata);
}



/**
 * NAME         anyka_start_picture
 * @BRIEF	����һ��ͼƬ������
 * @PARAM	mydata           �û�����
                    psend_video_callback    ���緢��ͼƬ�Ļص�
 * @RETURN	void
 * @RETVAL	
 */
 

void anyka_start_picture(void *mydata, P_VIDEO_DOWITH_CALLBACK psend_video_callback)
{
    video_add(psend_video_callback,mydata, FRAMES_ENCODE_PICTURE, 500);
}


/**
 * NAME         anyka_set_video_iframe
 * @BRIEF	ǿ�н���������Ϊ֡
 * @PARAM	mydata           �û�����
                   
 * @RETURN	NONE
 * @RETVAL	
 */
void anyka_set_video_iframe(void *mydata)

{
    video_set_iframe(mydata);
}

/**
 * NAME         anyka_start_video
 * @BRIEF	��������Ƶ�������޸�������Ƶ����
 * @PARAM	video_quality   ��Ƶ����������
                    mydata           �û�����
                    psend_video_callback    �û��ص����������ڷ�����������,���Ϊ�գ������޸Ĳ�����
                                                     ��Ϊ�ս����¿�������
 * @RETURN	������Ƶ��֡��
 * @RETVAL	
 */
int anyka_start_video(int video_quality, void *mydata, P_VIDEO_DOWITH_CALLBACK psend_video_callback)
{

    int video_bps, video_type, frames;    
    Psystem_cloud_set_info sys_setting;    
    video_setting *pvideo_default_config = anyka_get_sys_video_setting();
    
    Psystem_onvif_set_info onvif_setting = anyka_get_sys_onvif_setting();
    
    sys_setting = anyka_get_sys_cloud_setting();
    if(video_quality >= HIGH_BPS)
    {
        video_quality = HIGH_BPS;
    }
    
    if(video_quality >= NORMAL_BPS)
    {
        frames = onvif_setting->fps1;
        video_type = FRAMES_ENCODE_RECORD;
        video_bps = onvif_setting->kbps1;
    }
    else if(video_quality >= BPS_DIVIDE)
    {
        
        #ifdef  CONFIG_ONVIF_SUPPORT
        if(sys_setting->onvif)
        {
            frames = pvideo_default_config->VGAPfps;
            video_type = FRAMES_ENCODE_VGA_NET;
            video_bps = pvideo_default_config->VGAmaxkbps;
        }
        else
        #endif
        {
            frames = pvideo_default_config->V720Pfps;
            video_type = FRAMES_ENCODE_720P_NET;
            video_bps = pvideo_default_config->V720Pminkbps + (pvideo_default_config->V720Pmaxkbps - pvideo_default_config->V720Pminkbps) * (video_quality - BPS_DIVIDE) / (NORMAL_BPS - BPS_DIVIDE);
        }
    }
    else 
    {
        frames = pvideo_default_config->VGAPfps;
        video_type = FRAMES_ENCODE_VGA_NET;
        video_bps = pvideo_default_config->VGAminkbps + (pvideo_default_config->VGAmaxkbps - pvideo_default_config->VGAminkbps) * video_quality  / BPS_DIVIDE;
    }
    
    if(psend_video_callback)
    {
        video_add(psend_video_callback,mydata, video_type, video_bps);
    }
    else
    {
        video_change_attr(mydata, video_type, video_bps);
    }
    return frames;
}


/**
 * NAME         anyka_start_video_withbps
 * @BRIEF	��������Ƶ�������޸�������Ƶ����
 * @PARAM
            video_type 720P����VGA
            bps   ��Ƶ������
            mydata           �û�����
            psend_video_callback    �û��ص����������ڷ�����������,���Ϊ�գ������޸Ĳ�����
                                                     ��Ϊ�ս����¿�������
 * @RETURN	������Ƶ��֡��
 * @RETVAL	
 */
int anyka_start_video_withbps(int video_type, int video_bps, void *mydata, P_VIDEO_DOWITH_CALLBACK psend_video_callback)
{
    int frames;    
    video_setting *pvideo_default_config = anyka_get_sys_video_setting();
        
    if(video_type == FRAMES_ENCODE_720P_NET)
    {        
        frames = pvideo_default_config->V720Pfps;
    }
    else 
    {
        frames = pvideo_default_config->VGAPfps;
    }
    
    if(psend_video_callback)
    {
        video_add(psend_video_callback,mydata, video_type, video_bps);
    }
    else
    {
        video_change_attr(mydata, video_type, video_bps);
    }
    return frames;
}

/**
 * NAME         anyka_set_video_para
 * @BRIEF	�޸���Ƶ����Ĳ�����
 * @PARAM	video_type   �������ͣ�Ŀǰֻ֧��(1:720) OR (0:VGA)
            bps          ��Ƶ������
            mydata       �û�����
 * @RETURN	NONE
 * @RETVAL	
 */
void anyka_set_video_para(int video_type, int bps, void *mydata)
{
    video_change_attr(mydata, video_type, bps);
}


