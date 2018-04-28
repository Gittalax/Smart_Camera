#ifndef _anyka_photo_h_
#define _anyka_photo_h_


typedef void anyka_photo_callabck(void *parm, char *pic_path);

/**
 * NAME         anyka_photo_init
 * @BRIEF	���������̣߳��ȴ��û�����ָ��
 * @PARAM	photo_path  ���յ�·��
 * @RETURN	
 * @RETVAL	
 */

int anyka_photo_init(char *photo_path);


/**
 * NAME         anyka_photo_start
 * @BRIEF	��ʼ��������
 * @PARAM	total_time   ����ʱ�䣬���ս��������ʱ��,���Ϊ-1,����������
                    time_per_phone     ���յļ��ʱ��
                    photo_path  ���յ�·�������ΪNULL,��ʹ���ϴ����յ�·��
                    ppic_tell     ������ս�������֪ͨ�û�
                    para           �ص������Ĳ���
 * @RETURN	
 * @RETVAL	
 */

int anyka_photo_start(int total_time, int time_per_phone, char *photo_path, anyka_photo_callabck *ppic_tell, void *para);


/**
 * NAME         anyka_photo_stop
 * @BRIEF	��ǰ����֮ǰ����������
 * @PARAM	void
 * @RETURN	void
 * @RETVAL	
 */

void anyka_photo_stop();

#endif

