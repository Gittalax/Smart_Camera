#include "common.h"
#include "anyka_interface.h"
#include "anyka_config.h"
#include "anyka_ini.h"
#include "ap_opt.h"


struct dcs_video_color {
	uint8 brightness, contrast, saturation, hue;
};

struct dcs_video_color color;

/**
* @brief  set camer para
* 
* @author liqing
* @date 2013-10-21
* @bright[in] bright
* @constast[in] constast
* @saturation[in]stauration
* @hue[in]hue
* @return int
* @retval if return 0 success, otherwise failed 
*/
int Set_Color(int bright, int constast, int saturation, int hue)
{
	color.brightness = bright ;
	color.contrast = constast ;
	color.saturation = saturation ;
	color.hue = hue ;

	//��Ϊֻ��7���������Գ���15
	bright /= 15;
	constast /= 15;
	saturation /= 15;
	hue /= 15;
	
	camera_set_gamma(constast);
	camera_set_saturation(saturation );
	camera_set_brightness(bright);
	return 0;	
}

/**
* @brief  Get camer para
* 
* @author liqing
* @date 2013-10-21
* @cl[out]return camer info
* @return int
* @retval if return 0 success, otherwise failed 
*/
int Get_Color(int *bright, int *constast, int *saturation, int *hue)
{
	*bright = color.brightness;
	*constast = color.contrast;
	*hue = color.hue;
	*saturation = color.saturation;
	return 0;
}

typedef enum
{
	HZCLOSE,
	HZ60,
	HZ50,
	HZAUTO,
	HZMAX,
}HZSET;

static int power_freq = 0;


/**
 * NAME         Set_Freq
 * @BRIEF	���õ�ԴƵ��
 * @PARAM	int freq��Ҫ���õĵ�ԴƵ��ֵ
 * @RETURN	int
 * @RETVAL	0
 */

int Set_Freq(int freq)
{


	int f = 0;
	if(freq == 0)
	{
		f = HZ60; 
	}
	else
	{
		f = HZ50;
	}
	if ( !camera_set_power_frequency( f ) )
		power_freq = freq;

	return 0;
}


/**
 * NAME         Get_Freq
 * @BRIEF	��ȡ��ԴƵ��
 * @PARAM	void
 * @RETURN	int
 * @RETVAL	���ص�ǰ��ԴƵ��
 */
int Get_Freq( void )
{
	return power_freq;
}


static int g_camerflipstate = 0;



/**
 * NAME         SetCamerFlip
 * @BRIEF	����ͼ����ֵ����ת����ת��
 * @PARAM	int state
 			Ҫ���õ�״ֵ̬
 * @RETURN	int
 * @RETVAL	0
 */

int SetCamerFlip(int state)
{
	g_camerflipstate = state;
	anyka_print("Set the flip %d \n", state);
	switch(g_camerflipstate)
	{
		case S_Upright:
			camera_set_normal();
			break;
		case S_Horizontal:
			camera_set_mirror();
			break;
		case S_Vertical:
			camera_set_vflip();
			break;
		case S_FLIP:
			camera_set_flip();
			break;
	}

	return 0;
}



/**
 * NAME         GetCamerFilp
 * @BRIEF	��ȡͼ����ֵ����ת����ת��
 * @PARAM	void
 * @RETURN	int
 * @RETVAL	��ǰ����״ֵ̬
 */

int GetCamerFilp( void )
{
	return g_camerflipstate;
}


/**
 * NAME         anyka_clear_all_resource
 * @BRIEF	��նԽ���������Դ
 * @PARAM	void *mydata
 			Ҫ��յ���Դ
 * @RETURN	void
 * @RETVAL	
 */

void anyka_clear_all_resource(void *mydata)
{
    audio_talk_stop(mydata);
    audio_speak_stop(mydata, SYS_AUDIO_ENCODE_G711);
    audio_speak_stop(mydata, SYS_AUDIO_ENCODE_AMR);
    anyka_stop_video(mydata);
}



/**
 * NAME         anyka_get_ap_list
 * @BRIEF	��ȡAP �б�
 * @PARAM	void
 * @RETURN	Panyka_ap_list
 * @RETVAL	ָ��AP �б��ָ��
 */

Panyka_ap_list anyka_get_ap_list()
{
    int i;
    Panyka_ap_list ap_list;
    struct ap_shop soft_ap_list;
	
    if(doWirelessSearch(&soft_ap_list))
    {
        return AK_NULL;
    }
	
    ap_list = (Panyka_ap_list)malloc(sizeof(anyka_ap_list));
    ap_list->ap_num = soft_ap_list.ap_num;
	
	anyka_print("\nWifi list:\n");
    for(i = 0; i < soft_ap_list.ap_num; i++)
    {
		ap_list->ap_info[i].enc_type = soft_ap_list.ap_list[i].security;
		ap_list->ap_info[i].quality = atoi(soft_ap_list.ap_list[i].sig_level);
        strcpy(ap_list->ap_info[i].essid, soft_ap_list.ap_list[i].ssid);
		
        /*anyka_print("id:%d, enc:%d,ssid:%s, quality:%d\n", i+1, soft_ap_list.ap_list[i].security, 
			soft_ap_list.ap_list[i].ssid, atoi(soft_ap_list.ap_list[i].sig_level));*/
    }
    return ap_list;
}



