#ifndef _video_fs_manage_h_
#define _video_fs_manage_h_
#include "basetype.h"

enum RECORD_APP
{
	RECORD_APP_PLAN,
	RECORD_APP_ALARM,
	RECORD_APP_NUM
};

typedef struct
{
	char prefix[32];
	char posfix[32];
}video_file_name_info;

typedef void video_find_record_callback(char *file_name, int file_size,int type);

/**
* @brief  video_fs_exist
* 		�����ļ�(  ·��)�Ƿ��Ѿ�����
* @date 	2015/3
* @param:	char * pstrFilePath��Ҫ����·��
* @return 	uint8
* @retval 	����-->1��������-->0
*/

int video_fs_create_dir(char * pstrRecPath );

/**
* @brief  video_fs_get_free_size
* 			��ȡָ��Ŀ¼��ʣ��ռ�
* @date 	2015/3
* @param:	char * path�� ָ��Ҫ��ȡ��Ϣ��·����ָ��
* @return 	uint32 
* @retval 	success--> ָ��ǰ·����ʣ��ռ䣬 failed--> -1
*/

uint32 video_fs_get_free_size(char * path);

/**
* @brief  video_fs_init_record_list
* 			 ��ʼ��¼���б�
* @date 	2015/3
* @param:	char * prec_path�� ���¼��·��
			unsigned short type��RECORD_REPLAY_TYPE �ƻ�¼�����ͣ�����Ϊ�ƶ��������
			video_find_record_callback *pcallback�� ��������Ļص�
* @return 	uint64 
* @retval 	success-->ָ��Ŀ¼�·���������ļ���С, ����-->-1
*/
uint64 video_fs_init_record_list(char * prec_path, video_find_record_callback *pcallback, unsigned short type);


/**
* @brief  video_fs_get_audio_record_name
* 			���ݲ���������Ƶ¼���ļ���
* @date 	2015/3
* @param:	char * path��·��
			char * file_name ���ļ���
			char *ext_name�� �ļ���׺��
* @return 	uint8 
* @retval 	success -->1, failed --> 0
*/

uint8 video_fs_get_audio_record_name(char * path, char *file_name, char *ext_name);

/**
* @brief  video_fs_get_video_record_name
* 			���ݲ���������Ƶ¼���ļ���
* @date 	2015/3
* @param:	char * path��·��
			char * file_name ���ļ���
			char *ext_name�� �ļ���׺��
			time_t file_time ,     �ļ�����ʱ��
* @return 	uint8 
* @retval 	success -->1, failed --> 0
*/

uint8 video_fs_get_video_record_name(char * path, char *file_name, char *ext_name,time_t file_time);


/**
 * NAME     	video_fs_get_alarm_record_name
 * @BRIEF	according to param alarm_type, create respectively file name.
 * @PARAM	void *, now no use
 * @RETURN	void *
 * @RETVAL	
 */
uint8 video_fs_get_alarm_record_name(int alarm_type,char * path, char *file_name, char *ext_name);

/**
* @brief  video_fs_get_audio_record_name
* 			���ݲ������������ļ����ļ���
* @date 	2015/3
* @param:	char * path��·��
			char * file_name ���ļ���
* @return 	uint8 
* @retval 	success -->1, failed --> 0
*/
uint8 video_fs_get_photo_name(char * path, char *file_name);


/**
* @brief  video_fs_find_record_file
* 			 ��������Ŀ¼������ƥ����ļ� 
* @date 	2015/3
* @param:	char * prec_path�� ���Ƚϵ�Ŀ¼
			unsigned short type��RECORD_REPLAY_TYPE �ƻ�¼�����ͣ�����Ϊ�ƶ��������
			video_find_record_callback *pcallback�� ��������Ļص�
* @return 	uint32 
* @retval 	success-->ָ��Ŀ¼�·���������ļ���С, ����-->-1
*/
uint32 video_fs_find_record_file(char* prec_path , video_find_record_callback *pcallback, unsigned short type);


/**
* @brief  anyka_fs_get_system
* 			��ȡϵͳʱ��
* @date 	2015/3
* @param:	void
* @return 	struct tm *
* @retval 	success--> ָ��ǰϵͳʱ��Ľṹ��ָ�룬 failed--> NULL
*/

struct tm * anyka_fs_get_system(void);


/**
* @brief  video_fs_get_file_name_cfg
* 			��ȡ����¼���ļ�����������Ϣ
* @date 	2015/9
* @param:	void
* @return 	 video_file_name_info * 
* @retval 	ָ��������Ϣ��һ������, RECORD_APP��Ϊ����
*/
const video_file_name_info * video_fs_get_file_name_cfg();

#endif


