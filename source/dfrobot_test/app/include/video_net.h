#ifndef _video_net_h_
#define _video_net_h_

/**
 * NAME         anyka_stop_video
 * @BRIEF	�ر�������Ƶ
 * @PARAM	mydata           �û����ݣ��˽ṹ��ָ��Ҫ��anyka_start_video����һ��
 * @RETURN	void
 * @RETVAL	
 */


void anyka_stop_video(void *mydata);


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

int anyka_start_video(int video_quality, void *mydata, P_VIDEO_DOWITH_CALLBACK psend_video_callback);



/**
 * NAME         anyka_start_picture
 * @BRIEF	����һ��ͼƬ������
 * @PARAM	mydata           �û�����
                    psend_video_callback    ���緢��ͼƬ�Ļص�
 * @RETURN	void
 * @RETVAL	
 */
 

void anyka_start_picture(void *mydata, P_VIDEO_DOWITH_CALLBACK psend_video_callback);


/**
 * NAME         anyka_set_video_iframe
 * @BRIEF	ǿ�н���������Ϊ֡
 * @PARAM	mydata           �û�����
                   
 * @RETURN	NONE
 * @RETVAL	
 */
void anyka_set_video_iframe(void *mydata);

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
int anyka_start_video_withbps(int video_type, int bps, void *mydata, P_VIDEO_DOWITH_CALLBACK psend_video_callback);


/**
 * NAME         anyka_set_video_para
 * @BRIEF	�޸���Ƶ����Ĳ�����
 * @PARAM	video_type   �������ͣ�Ŀǰֻ֧��(1:720) OR (0:VGA)
            bps          ��Ƶ������
            mydata       �û�����
 * @RETURN	NONE
 * @RETVAL	
 */
 
void anyka_set_video_para(int video_type, int bps, void *mydata);

#endif


