#ifndef _anyka_interface_h_
#define _anyka_interface_h_


typedef enum
{
	S_Upright=0,
	S_Horizontal,
	S_Vertical,
	S_FLIP	
}T_CAMER_FLIP_STATE;

typedef struct _anyka_ap_info {
    char essid[33];
    uint32_t enc_type;
    uint32_t quality;
} anyka_ap_info, *Panyka_ap_info;

typedef struct _anyka_ap_list{
    int ap_num;
    anyka_ap_info ap_info[32];
} anyka_ap_list, *Panyka_ap_list;

/**
 * NAME         GetCamerFilp
 * @BRIEF	��ȡͼ����ֵ����ת����ת��
 * @PARAM	void
 * @RETURN	int
 * @RETVAL	��ǰ����״ֵ̬
 */

int GetCamerFilp( void );


/**
 * NAME         SetCamerFlip
 * @BRIEF	����ͼ����ֵ����ת����ת��
 * @PARAM	int state
 			Ҫ���õ�״ֵ̬
 * @RETURN	int
 * @RETVAL	0
 */

int SetCamerFlip(int state);

/**
 * NAME         anyka_clear_all_resource
 * @BRIEF	��նԽ���������Դ
 * @PARAM	void *mydata
 			Ҫ��յ���Դ
 * @RETURN	void
 * @RETVAL	
 */

void anyka_clear_all_resource(void *mydata);

/**
* @brief  Get camer para
* 
* @author liqing
* @date 2013-10-21
* @cl[out]return camer info
* @return int
* @retval if return 0 success, otherwise failed 
*/
int Get_Color(int *bright, int *constast, int *saturation, int *hue);

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
int Set_Color(int bright, int constast, int saturation, int hue);

/**
 * NAME         Set_Freq
 * @BRIEF	���õ�ԴƵ��
 * @PARAM	int freq��Ҫ���õĵ�ԴƵ��ֵ
 * @RETURN	int
 * @RETVAL	0
 */

int Set_Freq(int freq);

/**
 * NAME         Get_Freq
 * @BRIEF	��ȡ��ԴƵ��
 * @PARAM	void
 * @RETURN	int
 * @RETVAL	���ص�ǰ��ԴƵ��
 */

int Get_Freq( void );

/**
 * NAME         SetCamerFlip
 * @BRIEF	����ͼ����ֵ����ת����ת��
 * @PARAM	int state
 			Ҫ���õ�״ֵ̬
 * @RETURN	int
 * @RETVAL	0
 */

int SetCamerFlip(int state);

/**
 * NAME         anyka_clear_all_resource
 * @BRIEF	��նԽ���������Դ
 * @PARAM	void *mydata
 			Ҫ��յ���Դ
 * @RETURN	void
 * @RETVAL	
 */

int GetCamerFilp( void );

/**
 * NAME         anyka_get_ap_list
 * @BRIEF	��ȡAP �б�
 * @PARAM	void
 * @RETURN	Panyka_ap_list
 * @RETVAL	ָ��AP �б��ָ��
 */

Panyka_ap_list anyka_get_ap_list();

#endif

