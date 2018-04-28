#ifndef _ANYKA_INI_H_
#define _ANYKA_INI_H_
/**
* @brief  ��ʼ�������ļ�ϵͳ������ɴ������ļ���ȡ���ݣ���������ݽṹ�ĳ�ʼ��
* 
* @author aijun
* @date 2014-11-28
* @param[in]  void *config_name �����ļ���
* @return T_S32
* @retval if return 0 fail, otherwise the handle of the config
*/

void * anyka_config_init(char *config_name);



/**
* @brief  �ͷ����þ����������ڴ�,�������������仯���������ļ�
* 
* @author aijun
* @date 2014-11-28
* @param[in]  void *config_name  �����ļ���
                     void *config_handle �����ļ����
* @return T_S32
* @retval none
*/

int anyka_config_destroy(char *config_name, void *config_handle);



/**
* @brief  ���������ļ������ֵ,ֻ���ã���������,ֻд�뻺��
* 
* @author aijun
* @date 2014-11-28
* @param[in]  void *config_handle �����ļ����
                     char *title   ����ͷ��
                     char *name ����������
                     char *value Ҫ���õ�ֵ
* @return int
* @retval if return 0 success, otherwise failed 
*/

int anyka_config_set_title(void *config_handle, char *title, char *name, char *value);



/**
* @brief �õ������ļ������ֵ��û�д��ļ��������Ǵ�֮ǰ�Ļ����ж�ȡ
* 
* @author aijun
* @date 2014-11-28
* @param[in]  void *config_handle �����ļ����
                     char *title   ����ͷ��
                     char *name ����������
                     char *value Ҫ���õ�ֵ
* @return int
* @retval if return 0 success, otherwise failed 
*/

//int anyka_config_get_title(void *config_handle, char *title, char *name, char *value);
int anyka_config_get_title(void *config_handle, char *title, char *name, char *value, char *default_value);




/**
* @brief  ���������ļ������ֵ,ֻ���ã���ֱ���޸������ļ��������
* 
* @author aijun
* @date 2014-11-28
* @param[in]  void *config_handle �����ļ����
                     char *title   ����ͷ��
                     char *name ����������
                     char *value Ҫ���õ�ֵ
* @return int
* @retval if return 0 success, otherwise failed 
*/

int anyka_config_set_item(char *config_name, char *title, char *name, char *value);


/**
* @brief �õ������ļ������ֵ,��ֱ�Ӵ��ļ��ж�ȡ��
* 
* @author aijun
* @date 2014-11-28
* @param[in]  char *config_name �����ļ���
                     char *title   ����ͷ��
                     char *name ����������
                     char *value Ҫ���õ�ֵ
* @return int
* @retval if return 0 success, otherwise failed 
*/

//int anyka_config_get_item(char *config_name, char *title, char *name, char *value);
int anyka_config_get_item(char *config_name, char *title, char *name, char *value, char *default_value);



#endif

