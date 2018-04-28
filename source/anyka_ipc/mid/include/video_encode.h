#ifndef _ENCODE_H
#define _ENCODE_H 

#include "anyka_types.h"
#ifdef __cplusplus
extern "C"
{
#endif

enum ENCODE_TYPE
{
    H264_ENC_TYPE,
    MJPEG_ENC_TYPE
};

typedef struct _ENC_INPUT_PAR
{
	T_U32	width;			//ʵ�ʱ���ͼ��Ŀ�ȣ��ܱ�4����
	T_U32	height;			//ʵ�ʱ���ͼ��ĳ��ȣ��ܱ�2���� 
	T_U32	lumWidthSrc;	//cropping����ʱʹ�ã���ʾԭʼͼ��Ŀ��
	T_U32	lumHeightSrc;	//cropping����ʱʹ�ã���ʾԭʼͼ��ĸ߶�
	T_S32	qpHdr;			//��ʼ��QP��ֵ
	T_S32	iqpHdr;			//��ʼ��i֡��QPֵ
	T_S32   minQp;		    //��̬���ʲ���[20,25]
	T_S32   maxQp;		    //��̬���ʲ���[45,50]
	T_S32   framePerSecond; //֡��
	T_S32   gopLen;         //IP FRAME���
	T_S32	bitPerSecond;	//Ŀ��bps
	T_U32 	encode_type;
	T_U32 	video_mode;
}T_ENC_INPUT;

/**
* @brief  init vedio encoder
* 
* @author dengzhou
* @date 2013-04-07
* @param[in] 
* @return T_S32
* @retval if return 0 success, otherwise failed 
*/
int video_encode_init(void);

/**
* @brief  open vedio encoder
* 
* @author dengzhou
* @date 2013-04-07
* @param[in] 
* @return void *
* @retval if return the video handle success, otherwise NULL 
*/
void *video_encode_open(T_ENC_INPUT *pencInput);

/**
* @brief  encode one frame
* 
* @author dengzhou
* @date 2013-04-07
* @param[in] 
* @return T_S32
* @retval if return the frame size success, otherwise 0 
*/
int video_encode_frame(T_VOID * pencode_handle, void *pinbuf2, void **poutbuf2, int* nIsIFrame2);

/**
* @brief  close vedio encoder
* 
* @author dengzhou
* @date 2013-04-07
* @param[in] 
* @return T_S32
* @retval if return 0 success, otherwise failed 
*/
int video_encode_close(void * pencode_handle);

/**
* @brief  destroy vedio encoder
* 
* @author dengzhou
* @date 2013-04-07
* @param[in] 
* @return T_S32
* @retval if return 0 success, otherwise failed 
*/
int video_encode_destroy(void);

int video_encode_reSetRc(T_VOID * pencode_handle, int qp );

void video_encode_set_Iframe(T_VOID * pencode_handle);

#ifdef __cplusplus
}
#endif
#endif /* _ENCODE_H */
