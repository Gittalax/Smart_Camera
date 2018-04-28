#ifndef __SYS_INTERFACE_H__
#define __SYS_INTERFACE_H__

#include <stdbool.h>

struct smartlink_wifi_info {
	char ssid[128];
	char passwd[128];
};

/**
* @brief ���ļ���ȡָ����������
* @author ye_guohong
* @date 2015-03-31
* @param[in]    pPath       �ļ���
* @param[out]   pBuffer     ��ȡ���ݴ��λ��
* @param[out]   nInSize     �Ѷ�ȡ���ݳ���
* @return bool
* @retval if return true success, otherwise failed
*/
bool readBufferFromFile(char *pPath, unsigned char *pBuffer, int nInSize, int *pSizeUsed);

/**
 * @brief ����smartlink��ip��ַ�Ͷ˿ں���Ϣ����ʱ�ļ�
 * @param[in] ip  ip��ַ
 * @param[in] port �˿ں�
 */
void save2file(char *ip, int port);

/**
* @brief �洢wifi������Ϣ�����
* @author ye_guohong
* @date 2015-03-31
* @param[in]    wifi_info       wifi������Ϣ�ṹ��
* @return int
* @retval if return 0 success, otherwise failed
*/
int store_wifi_info(struct smartlink_wifi_info *wifi_info);

/**
* @brief save_ssid_to_tmp
* 		 save the ssid to tmp file
* @author cyh
* @date 2015-11-05
* @param[in]  ssid
* @return int
* @retval if return 0 success, otherwise failed
*/

int save_ssid_to_tmp(char *ssid, unsigned int ssid_len);

#endif
