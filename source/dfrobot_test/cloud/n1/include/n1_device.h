
/**
 * N1 �豸 API �ӿڡ�
 */

#include <NkUtils/n1_def.h>

#ifndef NK_N1_DEVICE_H_
#define NK_N1_DEVICE_H_
NK_CPP_EXTERN_BEGIN




/**
 * @brief N1 �豸ģ������ʱ�����ġ�
 */
typedef struct Nk_N1Device
{
	/**
	 * ��ǰ�豸�����кš�\n
	 * �û��ڳ�ʼ����ʱ���룬��Ϊ���豸�ھ����������ӵ�Ψһ�ԡ�\n
	 * �������ô�ֵ�����ڲ����������һ���ַ�����Ϊ��ǰ�豸��Ψһ��ʶ��
	 */
	NK_Char device_id[128];

	/**
	 * ���豸���кš�\n
	 * �����к����豸�ڻ�����ͨѶ��Ψһ����룬������ʱͳһ���䲢��¼���豸���С�
	 */
	NK_Char cloud_id[32];

	/**
	 * ģ�����ڼ��������¼��Ķ˿ڡ�\n
	 * ����ģ��ʹ���������ӷ�ʽΪ TCP��������ô˶˿�ʱע�ⲻ����ģ����������� TCP �󶨶˿ڳ�ͻ��\n
	 * ����ʹ�� 1024 ���ϵĶ˿ڡ�
	 */
	NK_UInt16 port;

	/**
	 * �û������ġ�\n
	 * ����ģ�鴥���¼�ʱ���û��ⲿ�������ݡ�
	 */
	NK_PVoid user_ctx;


	struct {

		/**
		 * ��ý���ֳ�ץͼ�¼���\n
		 * �ͻ�����ҪԤ��������ֳ�ͼƬ��ʱ�������˽ӿ����豸��ȡһ���ֳ�����ͼ��\n
		 * ����ͼֻ֧�� JPEG �ļ���ʽ��
		 *
		 * @param[in]		channel_id		ץͼͨ������ 0 ��ʼ��
		 * @param[in]		width			ͼƬ��ȡ�
		 * @param[in]		height			ͼƬ�߶ȡ�
		 * @param[in]		pic				ͼƬ���塣
		 * @param[in,out]	size			����/ͼƬ��С��
		 *
		 * @retval NK_N1_ERR_NONE					�ֳ�ץͼ�ɹ���
		 * @retval NK_N1_ERR_DEVICE_BUSY			�豸æµ���ͻ����п��ܻᶨʱ���ԡ�
		 * @retval NK_N1_ERR_DEVICE_NOT_SUPPORT		�豸��֧�ִ�ץͼ���ܣ��ͻ��ν����ٶԸ��豸����ץͼ��
		 *
		 */
		NK_N1Error
		(*onLiveSnapshot)(NK_Int channel_id, NK_Size width, NK_Size height, NK_PByte pic, NK_Size *size);


		/**
		 * ��ý��ֱ�������¼���\n
		 * �ͻ�������ʱ�ᴥ�����¼���\n
		 * ʵ��ʱ���ݴ���� Session::channel_id �� Session::stream_id ��Ӧ�豸�����\n
		 * ��ʼ���Ự @ref Session ���ݽṹ��\n
		 * �����ݾ���ʵ�����������Ե���ֵ����ģ��������Ӧ����Ӧ��\n
		 * ���� @ref Session::user_session ���ڱ����û��Ự��\n
		 * ʵ��ʱ���Ա���ʵʩý�������Դ�����Ϣ��\n
		 *
		 *
		 * @param[in,out]	Session			�Ự�����ģ�ģ��ͨ���Ự��������ʵ�ֹ������ݡ�
		 * @param[in,out]	ctx				�û������ģ��ڵ��ýӿ� @ref NK_N1Device_Init ʱ���롣
		 *
		 * @retval NK_N1_ERR_NONE					���ӳɹ����ͻ��˼�����ȡ����ý�����ݡ�
		 * @retval NK_N1_ERR_DEVICE_BUSY			�豸æµ�����û�ý��Դ��Դ����ʧ��ʱ���ش�ֵ��
		 * @retval NK_N1_ERR_DEVICE_NOT_SUPPORT		�豸��֧�ִ��������󣬵��ͻ��������ͨ�������������豸�ṩ�ķ�Χ���ش��¡�
		 * @retval NK_N1_ERR_NOT_AUTHORIZATED		�û�У��ʧ�ܣ�����ͻ��˶�Ӧ�û����߱���ý��ֱ��Ȩ�ޡ�
		 *
		 */
		NK_N1Error
		(*onLiveConnected)(NK_N1LiveSession *Session, NK_PVoid ctx);

		/**
		 * ��ý��ֱ���Ͽ��¼���\n
		 * �ͻ��˶Ͽ�����ʱģ��ᴥ�����¼���\n
		 *
		 * @param[in,out]	Session			�Ự�����ģ�ģ��ͨ���Ự��������ʵ�ֹ������ݡ�
		 * @param[in,out]	ctx				�û������ģ��ڵ��ýӿ� @ref NK_N1Device_Init ʱ���롣
		 *
		 * @retval NK_N1_ERR_NONE					�Ͽ��ɹ����ͻ��˲��ٻ�ȡ����ý�����ݡ�
		 *
		 */
		NK_N1Error
		(*onLiveDisconnected)(NK_N1LiveSession *Session, NK_PVoid ctx);

		/**
		 * ��ý��ֱ����ȡ�¼���\n
		 * ����ý�屻�㲥ʱ���ͻ��˻�ȡý��֡���ݻᴥ�����¼���
		 *
		 * @param[in,out]	Session			�Ự�����ģ�ģ��ͨ���Ự��������ʵ�ֹ������ݡ�
		 * @param[in,out]	ctx				�û������ģ��ڵ��ýӿ� @ref NK_N1Device_Init ʱ���롣
		 * @param[out]		payload_type	��ȡ�������������͡�
		 * @param[out]		ts_ms			��ȡ������ʱ�������λ�����룩��
		 * @param[out]		data_r			��ȡ�����������ڴ�ĵ�ַ��
		 *
		 * @retval ����0								��ȡ�ɹ�����ȡ�����ݳ��ȡ�
		 * @retval ����0								��ȡʧ�ܣ�û�����ݿɶ���
		 * @retval С��0								��ȡʧ�ܣ���ȡʱ����������Ҫ�˳����Ự��
		 *
		 */
		NK_SSize
		(*onLiveReadFrame)(NK_N1LiveSession *Session, NK_PVoid ctx,
				NK_N1DataPayload *payload_type, NK_UInt32 *ts_ms, NK_PByte *data_r);

		/**
		 * ��ý��ֱ����ȡ�����¼���\n
		 * �ڴ����¼� @ref onLiveReadFrame() ����ڲ����������ݵ��ڴ��ַ��\n
		 * ��ʹ�����ⲿ�������Ժ�ᴥ�����¼��������û��ͷ����õ�������Դ��
		 *
		 *
		 * @param[in,out]	Session			�Ự�����ģ�ģ��ͨ���Ự��������ʵ�ֹ������ݡ�
		 * @param[in,out]	ctx				�û������ģ��ڵ��ýӿ� @ref NK_N1Device_Init ʱ���롣
		 * @param[in]		data_r			�����¼� @ref onLiveReadFrame() ʱ���õ������ڴ��ַ��
		 * @param[in]		size			�����¼� @ref onLiveReadFrame() ʱ���õ����ݴ�С��
		 *
		 * @retval NK_N1_ERR_NONE					�����ɹ���
		 */
		NK_N1Error
		(*onLiveAfterReadFrame)(NK_N1LiveSession *Session, NK_PVoid ctx,
				NK_PByte *data_r, NK_Size size);


		/**
		 * �����������¼���
		 *
		 * @param[in,out]	ctx				�û������ģ��ڵ��ýӿ� @ref NK_N1Device_Init ʱ���롣
		 * @param[in]		set_or_get		����/��ȡ��ʶ������ֵΪ True ʱ�� Setup Ϊ�����������֮Ϊ����������
		 * @param[in,out]	Setup			�������ݽṹ��
		 *
		 * @retval NK_N1_ERR_NONE					���û�����ɹ���
		 * @retval NK_N1_ERR_DEVICE_NOT_SUPPORT		�豸��֧�ָ����û������
		 * @retval NK_N1_ERR_INVALID_PARAM			���û������������Ч�Ĳ�����
		 * @retval NK_N1_ERR_NOT_AUTHORIZATED		�û�У��ʧ�ܣ�����ͻ��˶�Ӧ�û����߱�������Ȩ�ޡ�
		 */
		NK_N1Error
		(*onLanSetup)(NK_PVoid ctx, NK_Boolean set_or_get, NK_N1LanSetup *Setup);


		/**
		 * ɨ�������ȵ��¼���\n
		 * ��ģ����Ҫ��⸽���� WiFi NVR ��ʱ�򴥷����¼���\n
		 * �û�ͨ��ʵ�ִ˽ӿڣ���֪ģ�鸽���� WiFi �ȵ���Ϣ��
		 *
		 * @param[in,out]	ctx				�û������ģ��ڵ��ýӿ� @ref NK_N1Device_Init ʱ���롣
		 * @param[out]		HotSpots		�ȵ����ݽṹջ�����塣
		 * @param[in,out]	n_hotSpots		�����ȵ����ݽṹջ���Ļ��壬����ʵ��ɨ�赽�ȵ��������
		 *
		 * @retval NK_N1_ERR_NONE					ɨ���ȵ�ɹ������������ @ref HotSpots �����С�
		 *
		 */
		NK_N1Error
		(*onScanWiFiHotSpot)(NK_PVoid ctx, NK_WiFiHotSpot *HotSpots, NK_Size *n_hotSpots);


		/**
		 * ���������ȵ��¼���\n
		 * ����֧���������ӵ��豸����ģ��ϣ���û�����ĳ�� NVR �豸��ʱ��ᴥ�����¼���\n
		 * �������¼�ʱ��ͬ���ᷢ��һ������ @ref NK_N1LanSetup::WiFiNVR ���¼���\n
		 * �� @ref onLanSetup �¼���ͬ��ʱ�����﷢������ @ref NK_N1LanSetup::WiFiNVR ���¼�ʱ��\n
		 * �û�����Ҫ���� @ref NK_N1LanSetup::WiFiNVR ���������ݣ�\n
		 * �� @ref onLanSetup �¼�����Ҫ�û����� @ref NK_N1LanSetup::WiFiNVR ��Ӧ���ݽṹ��\n
		 *
		 * @param[in,out]	ctx				�û������ģ��ڵ��ýӿ� @ref NK_N1Device_Init ʱ���롣
		 * @param[in,out]	Setup			�������������ݽṹ��
		 *
		 * @retval NK_N1_ERR_NONE					�����ȵ�ɹ���
		 */
		NK_N1Error
		(*onConnectWiFiHotSpot)(NK_PVoid ctx, NK_N1LanSetup *Setup);


		/**
		 * �û������¼���\n
		 * ��У���û�״̬����ʱ�ᴥ�����¼���\n
		 * ʵ�ִ˽ӿڱ������µ��û����ݡ�
		 *
		 * @param[in,out]	ctx				�û������ģ��ڵ��ýӿ� @ref NK_N1Device_Init ʱ���롣
		 *
		 * @retval NK_N1_ERR_NONE				�����ɹ���
		 */
		NK_N1Error
		(*onUserChanged)(NK_PVoid ctx);


	} EventSet;


} NK_N1Device;


/**
 * ��ȡ N1 �汾�š�\n
 * �����ж϶����ƿ��ļ���ͷ�ļ��Ƿ�ƥ�䣬�����������ݽṹ��С��ƥ�������Ǳ�ڵ����⡣
 *
 * @param[out]			ver_maj				�� NK_N1_VER_MAJ ��Ӧ��
 * @param[out]			ver_min				�� NK_N1_VER_MIN ��Ӧ��
 * @param[out]			ver_rev				�� NK_N1_VER_REV ��Ӧ��
 * @param[out]			ver_num				�� NK_N1_VER_NUM ��Ӧ��
 *
 */
extern NK_Void
NK_N1Device_Version(NK_UInt32 *ver_maj, NK_UInt32 *ver_min, NK_UInt32 *ver_rev, NK_UInt32 *ver_num);


/**
 * ��ʼ�� N1 �豸���л�����
 *
 * @param[in]			Device				�豸��ʼ����������û������롣
 *
 * @return		�ɹ����� 0��ʧ�ܷ��� -1��
 */
extern NK_Int
NK_N1Device_Init(NK_N1Device *Device);

/**
 * ���� N1 �豸���л�����\n
 * ���ô˽ӿ�ǰ��Ҫ�ȵ��� @ref NK_N1Device_Init �ӿڴ˽ӿڲ��ܳɹ����ء�\n
 * ���ӿڳɹ����� 0 ʱ������ͨ�� @ref user_ctx_r ��ȡ @ref NK_N1Device_Init ������û������ġ�\n
 * �����߿�һ��������������ͷŴ�����û������������Դ��
 *
 * @param[out]			Device				���س�ʼ��ʱ @ref NK_N1Device_Init ������û������ġ�
 *
 * @return		�ɹ����� 0��ʧ�ܷ��� -1��
 */
extern NK_Int
NK_N1Device_Destroy(NK_N1Device *Device);


/**
 * ��ͻ��˷���֪ͨ��Ϣ��
 *
 */
extern NK_Int
NK_N1Device_Notify(NK_N1Notification *Notif);


/**
 * WiFi NVR ��Կ��ơ�\n
 * ����豸�߱� Wi-Fi ���ӵ�����������ͨ�����ô˽ӿ�ʹ�豸�� Wi-Fi NVR ����������ӡ�\n
 * ���� @ref enabled �����˷�ʽʱ���� Wi-Fi NVR ��Ի��ǹرա�\n
 * ������ Wi-Fi NVR ���ʱ��\n
 * ���ں�̨����һ���̣߳�ά���� Wi-Fi NVR �������ӣ�ֱ���ر����λ�á�\n
 * ���� Wi-Fi NVR ά���������ӵ�ʱ��\n
 * �ᴥ�� NK_N1Device::EventSet::onScanHotSpots �� NK_N1Device::EventSet::onConnectWiFiHotSpot �¼���\n
 * �û�������Ͻӿ�ʵ�ֲ���ʹ Wi-Fi NVR ��Թ�������������
 *
 *
 * @param[in]			enabled				���� / �ر� Wi-Fi NVR ��Ա�ʶ��
 *
 * @return		�ɹ����� 0��ʧ�ܷ��� -1��
 */
extern NK_Int
NK_N1Device_PairWiFiNVR(NK_Boolean enabled);


/**
 * ����һ����֤�û���\n
 * ���������κε��û���Э������������ͨѶ�򲻽���У�顣
 *
 * @param[in]			username			�û����û����ơ�
 * @param[in]			password			�û���У�����롣
 * @param[in]			forbidden			�û���ֹȨ�ޣ�λ��Ч��Ŀǰ��ʹ�á�
 *
 * @return		�ɹ����� 0��ʧ�ܷ��� -1��
 */
extern NK_Int
NK_N1Device_AddUser(NK_PChar username, NK_PChar password, NK_UInt32 forbidden);


/**
 * ɾ��һ����֤�û���
 *
 * @param[in]			username			�û����û����ơ�
 *
 * @return		�ɹ����� 0��ʧ�ܷ��� -1��
 */
extern NK_Int
NK_N1Device_DeleteUser(NK_PChar username);

/**
 * ��ȡ��Ӧ�û����Ƶ���Ϣ��\n
 * ����û������򷢻Ӹ��û����û����� @ref password �ͽ�ֹȨ�ޱ�ʶ @ref forbiden_r��
 *
 * @param[in]			username			�û����û����ơ�
 * @param[out]			password			�û���У�����롣
 * @param[out]			forbidden_r			�û���ֹȨ�ޱ�ʶ��
 *
 * @return		�û����ڷ��� True������ @ref password �� @ref forbidden_r ��ȡ�����Ϣ���û��������򷵻� False��
 */
extern NK_Boolean
NK_N1Device_HasUser(NK_PChar username, NK_PChar password, NK_UInt32 *forbidden_r);


/**
 * ��ȡ��֤���û�����
 *
 * @return		�û�����������û�����Ϊ 0��������ͨѶ�����κ���֤��
 */
extern NK_Size
NK_N1Device_CountUser();

/**
 * ��ȡ���кŶ�Ӧ���û���Ϣ��\n
 * һ�����ڱ���������
 *
 * @param[in]			id					�û���š�
 * @param[out]			username			�û����û����ơ�
 * @param[out]			password			�û���У�����롣
 * @param[out]			forbidden_r			�û���ֹȨ�ޱ�ʶ��
 *
 * @return		�û������򷵻� 0�����ҴӲ����з����û���Ϣ��ʧ�ܷ��� -1��
 */
extern NK_Int
NK_N1Device_IndexOfUser(NK_Int id, NK_PChar username, NK_PChar password, NK_UInt32 *forbidden_r);


NK_CPP_EXTERN_END
#endif /* NK_N1_DEVICE_H_ */
