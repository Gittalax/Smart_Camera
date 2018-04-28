#ifndef _ANYKA_QUEUE_H_
#define _ANYKA_QUEUE_H_
#include "basetype.h"

typedef void anyka_queue_free(void *item);
typedef int anyka_queue_compare(void *item1, void *item2);

/**
 * NAME         anyka_queue_init
 * @BRIEF	���г�ʼ��
 * @PARAM	max_item : ��������󴢴���
 
 * @RETURN	���о��
 * @RETVAL	
 */

void * anyka_queue_init(int max_item);


/**
 * NAME         anyka_queue_destroy
 * @BRIEF	�����ͷţ����ͷŶ���������δ����������ֻ�ͷ���Ӧ�ڴ�
                    ϵͳ����ʧ��������
 * @PARAM	queue_handle : ���о��
                    queue_free     :�����ͷ���������ڴ�ص�
 
 * @RETURN	NONE
 * @RETVAL	
 */

void anyka_queue_destroy(void * queue_handle, anyka_queue_free *queue_free);


/**
 * NAME         anyka_queue_push
 * @BRIEF	���û����ݷ��������
 * @PARAM	queue_handle : ���о��
                    data  �û�����ָ��
 * @RETURN	����β������
 * @RETVAL	0-->fail; 1-->ok
 */

uint8 anyka_queue_push(void * queue_handle, void *data);

/**
 * NAME         anyka_queue_pop
 * @BRIEF	���û����ݷ��ظ��û��������е�����������
 * @PARAM	queue_handle : ���о��
                    
 * @RETURN	���ض���ͷ����
 * @RETVAL	
 */

void * anyka_queue_pop(void * queue_handle);

/**
 * NAME         anyka_queue_sort
 * @BRIEF	�Զ����е��������������
 * @PARAM	queue_handle : ���о��
                    compare         :������Ƚϻص�����
 * @RETURN	NONE
 * @RETVAL	
 */

void anyka_queue_sort(void * queue_handle, anyka_queue_compare *compare);

/**
 * NAME         anyka_queue_not_empty
 * @BRIEF	�ж϶����Ƿ�Ϊ��
 * @PARAM	queue_handle : ���о��
 
 * @RETURN	0-->empty; 1-->have
 * @RETVAL	
 */

uint8 anyka_queue_not_empty(void * queue_handle);

/**
 * NAME         anyka_queue_is_full
 * @BRIEF	�ж϶����Ƿ�Ϊ��
 * @PARAM	queue_handle : ���о��
 
 * @RETURN	0-->not full; 1-->full
 * @RETVAL	
 */

uint16 anyka_queue_is_full(void * queue_handle);


/**
 * NAME         anyka_queue_get_tail_note
 * @BRIEF	���ض���β���������������ڶ��е�λ��
 * @PARAM	queue_handle : ���о��
 
 * @RETURN	����β������
 * @RETVAL	
 */

void* anyka_queue_get_tail_note(void * queue_handle);

/**
 * NAME         anyka_queue_is_full
 * @BRIEF	���ض�����������Ŀ
 * @PARAM	queue_handle : ���о��
 
 * @RETURN	��������Ŀ
 * @RETVAL	
 */

uint16 anyka_queue_items(void * queue_handle);


/**
 * NAME         anyka_queue_is_full
 * @BRIEF	����ָ������������
 * @PARAM	queue_handle : ���о��
                    index              :���������
 * @RETURN	�û�������
 * @RETVAL	
 */

void* anyka_queue_get_index_item(void * queue_handle, int index);


#endif

