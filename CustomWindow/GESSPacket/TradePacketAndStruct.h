#pragma once
#include <string>
#include "TradePacket.h"
#include "ArrayListMsg.h"
#include "HashtableMsg.h"

using namespace std;

//----------------------------------------------��Ӧ���Ļ��� ����
// �ṹ����:��Ӧ���Ļ���
typedef struct tagRspBase
{
	string       rsp_msg              ;   
	string       rsp_code;
}RspBase,*PRspBase;

//----------------------------------------------Req���Ľӿ� [1001] ����
// �ṹ����:����ȡ����������
typedef struct tagReq1001
{
	int          oper_flag            ; //������־    1����ѯ
	string       code_type            ; //�������    
}Req1001,*PReq1001;


//----------------------------------------------Rsp���Ľӿ� [1001] ����
// �ṹ����:����ȡ����Ӧ������
typedef struct tagRsp1001 : public RspBase
{
	int          oper_flag            ; //������־    1����ѯ
	string       code_type            ; //�������    
	string       code_id              ; //������    
	string       code_desc            ; //��������    
	HashtableMsg htm_code_list        ; //����б�    �ֶ�Ϊ��������͡������š���������   
}Rsp1001,*PRsp1001;



//----------------------------------------------Req���Ľӿ� [1002] ����
// �ṹ����:��Լ�����趨
typedef struct tagReq1002
{
	int          oper_flag            ; //������־    1����ѯ2������3���޸�4��ɾ��
	string       prod_code            ; //��Լ����    
	string       prod_name            ; //��Լ����    
	string       variety_type         ; //Ʒ�����    
	string       variety_id           ; //Ʒ�ִ���    
	double       tick                 ; //��С�䶯��λ    
	double       upper_limit_value    ; //��ͣ����    
	double       lower_limit_value    ; //��ͣ����    
	string       active_flag          ; //��Ծ��־    
	string       exch_unit            ; //���׵�λ    
	double       measure_unit         ; //������λ    
	string       market_id            ; //�����г�    
}Req1002,*PReq1002;


//----------------------------------------------Rsp���Ľӿ� [1002] ����
// �ṹ����:��Լ�����趨
typedef struct tagRsp1002 : public RspBase
{
	int          oper_flag            ; //������־    1����ѯ2������3���޸�4��ɾ��
	string       prod_code            ; //��Լ����    
	string       prod_name            ; //��Լ����    
	string       variety_type         ; //Ʒ�����    
	string       variety_id           ; //Ʒ�ִ���    
	double       tick                 ; //��С�䶯��λ    
	double       upper_limit_value    ; //��ͣ����    
	double       lower_limit_value    ; //��ͣ����    
	string       active_flag          ; //��Ծ��־    
	string       exch_unit            ; //���׵�λ    
	double       measure_unit         ; //������λ    
	string       market_id            ; //�����г�    
	HashtableMsg htm_prod_code        ; //��Լ�����б�    �ֶΣ�2-12
}Rsp1002,*PRsp1002;

//----------------------------------------------Req���Ľӿ� [1004] ����
// �ṹ����:����Ʒ���趨
typedef struct tagReq1004
{
	int          oper_flag            ; //������־    1����ѯ2������3���޸�4��ɾ��
	string       variety_id           ; //����Ʒ�ִ���    
	string       name                 ; //����Ʒ��ȫ��            
	string       abbr                 ; //���                    
	string       variety_type         ; //Ʒ�����    
	double       min_pickup           ; //��С�������        
	double       pickup_base          ; //�������        
	string       weight_unit          ; //������λ        
	string       destroy_flag         ; //ע����־    
}Req1004,*PReq1004;


//----------------------------------------------Rsp���Ľӿ� [1004] ����
// �ṹ����:����Ʒ���趨
typedef struct tagRsp1004 : public RspBase
{
	int          oper_flag            ; //������־    1����ѯ2������3���޸�4��ɾ��
	string       variety_id           ; //����Ʒ�ִ���    
	string       name                 ; //����Ʒ��ȫ��            
	string       abbr                 ; //���                    
	string       variety_type         ; //Ʒ�����    
	double       min_pickup           ; //��С�������        
	double       pickup_base          ; //�������        
	string       weight_unit          ; //������λ        
	string       destroy_flag         ; //ע����־    
	HashtableMsg htm_variety_list     ; //����Ʒ���б�    �ֶ�Ϊ��2-9 
}Rsp1004,*PRsp1004;


//----------------------------------------------Req���Ľӿ� [1005] ����
// �ṹ����:�������Ʒ���趨
typedef struct tagReq1005
{
	int          oper_flag            ; //������־    1����ѯ2������3���޸�4��ɾ��
	string       prod_code            ; //��Լ����    
	double       seq_no               ; //����˳��    
	string       variety_id           ; //����Ʒ�ִ���    
	double       diff_amt             ; //���    
}Req1005,*PReq1005;


//----------------------------------------------Rsp���Ľӿ� [1005] ����
// �ṹ����:�������Ʒ���趨
typedef struct tagRsp1005 : public tagRspBase
{
	int          oper_flag            ; //������־    1����ѯ2������3���޸�4��ɾ��
	string       prod_code            ; //��Լ����    
	double       seq_no               ; //����˳��    
	string       variety_id           ; //����Ʒ�ִ���    
	double       diff_amt             ; //���    
	HashtableMsg htm_variety_info     ; //�������Ʒ���б�    �ֶ�Ϊ����Լ���룬����˳�򣬽���Ʒ�ִ��룬��� 
}Rsp1005,*PRsp1005;


//----------------------------------------------Req���Ľӿ� [1006] ����
// �ṹ����:�ֿ���Ϣά��
typedef struct tagReq1006
{
	int          oper_flag            ; //������־    1����ѯ2������3���޸�4��ɾ��
	string       stor_id              ; //�ֿ����    
	string       stor_name            ; //�ֿ�����    
	string       addr                 ; //�ֿ��ַ    
	string       tel                  ; //��ϵ�绰    
	string       fax                  ; //��ϵ����    
	string       link_man             ; //��ϵ��    
	string       zip_code             ; //�ʱ�    
	string       use_variety_type     ; //֧�ֵ����Ʒ��    ÿ��Ʒ������֮��ʹ�á�,���ָ�
	string       is_take              ; //�Ƿ��������    yes_no
	string       city_code            ; //��������    ������д���֮��ʹ�á�,���ָ�
}Req1006,*PReq1006;


//----------------------------------------------Rsp���Ľӿ� [1006] ����
// �ṹ����:�ֿ���Ϣά��
typedef struct tagRsp1006 : public tagRspBase
{
	int          oper_flag            ; //������־    1����ѯ2������3���޸�4��ɾ��
	string       stor_id              ; //�ֿ����    
	string       stor_name            ; //�ֿ�����    
	string       addr                 ; //�ֿ��ַ    
	string       tel                  ; //��ϵ�绰    
	string       fax                  ; //��ϵ����    
	string       link_man             ; //��ϵ��    
	string       zip_code             ; //�ʱ�    
	string       use_variety_type     ; //֧�ֵ����Ʒ��    ÿ��Ʒ������֮��ʹ�á�,���ָ�
	string       is_take              ; //�Ƿ��������    yes_no
	string       city_code            ; //��������    ������д���֮��ʹ�á�,���ָ�
	HashtableMsg htm_stor_info        ; //�ֿ���Ϣ�б�    �ֶ�Ϊ�� 2-11
}Rsp1006,*PRsp1006;



//----------------------------------------------Req���Ľӿ� [1007] ����
// �ṹ����:���д���ά������������
typedef struct tagReq1007
{
	int          oper_flag            ; //������־    1����ѯ2������3���޸�4��ɾ��
	string       city_code            ; //���д���    2*,3*,4*
	string       city_name            ; //��������    2*,3*
	string       all_stor_id          ; //�ֿ����    2*,3*
	string       stor_id_default      ; //Ĭ������ֿ�    2*,3*
}Req1007,*PReq1007;


//----------------------------------------------Rsp���Ľӿ� [1007] ����
// �ṹ����:����ȡ����Ӧ������
typedef struct tagRsp1007 : public tagRspBase
{
	int          oper_flag            ; //������־    1����ѯ2������3���޸�4��ɾ��
	string       city_code            ; //���д���    
	string       city_name            ; //��������    
	string       all_stor_id          ; //�ֿ����    2*,3*
	string       stor_id_default      ; //Ĭ������ֿ�    2*,3*
	HashtableMsg htm_code_list        ; //����б�    �ֶ�Ϊ��2-5 
}Rsp1007,*PRsp1007;

//----------------------------------------------Req���Ľӿ� [1020] ����
// �ṹ����:�ͻ��ۺ���Ϣ��ѯ
typedef struct tagReq1020
{
	int          oper_flag            ; //������־    1����ѯ
	string       acct_no              ; //�ͻ���    
	string       qry_cust_info        ; //��ѯ�ͻ�����    yes_no
	string       qry_fund             ; //��ѯ�ʽ���Ϣ    yes_no
	string       qry_storage          ; //��ѯ�����Ϣ    yes_no
	string       qry_forward          ; //��ѯԶ�ڳֲ���Ϣ    yes_no
	string       qry_defer            ; //��ѯ���ڳֲ���Ϣ    yes_no
	string       qry_surplus          ; //��ѯ����ӯ��    yes_no
	string       is_check_stat        ; //�Ƿ���״̬    yes_no
}Req1020,*PReq1020;


//----------------------------------------------Rsp���Ľӿ� [1020] ����
// �ṹ����:�ͻ��ۺ���Ϣ��ѯ
typedef struct tagRsp1020 : public tagRspBase
{
	int          oper_flag            ; //������־    
	string       c_acct_no            ; //�ͻ���    �D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�ͻ�����
	string       c_cust_id            ; //�ͻ�����    
	string       c_account_no         ; //�������˺�    
	string       c_open_bank_name     ; //����������    
	string       c_cust_abbr          ; //�ͻ����    
	string       c_b_fare_model_id    ; //����������ģ��ID    
	string       c_m_fare_model_id    ; //��Ա����ģ��ID    
	string       c_acct_type          ; //�˻�����    acct_type
	string       c_ocma_flag          ; //һ���໧��־    ocma_flag
	string       c_acct_stat          ; //�˻�״̬    acct_stat
	string       c_broker_acct_no     ; //�������˻�    
	string       c_cert_type          ; //֤������    cert_type
	string       c_cert_num           ; //֤������    
	string       c_branch_id          ; //�����������    
	string       c_trans_check_info   ; //������֤��Ϣ    
	string       f_currency_id        ; //����    �D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�ʽ����
	string       f_curr_bal           ; //��ǰ���    
	string       f_can_use_bal        ; //���ý��    
	string       f_can_get_bal        ; //������    
	string       f_in_bal             ; //�������    
	string       f_out_bal            ; //���ճ���    
	string       f_buy_bal            ; //������    
	string       f_sell_bal           ; //�������    
	string       f_exch_froz_bal      ; //���׶����ʽ�    
	string       f_posi_margin        ; //�ֱֲ�֤��    
	string       f_base_margin        ; //������֤��    
	string       f_take_margin        ; //�����֤��    
	string       f_stor_margin        ; //�ִ��ѱ�֤��    
	string       f_pt_reserve         ; //���𶳽��ʽ�    
	string       f_ag_margin          ; //���������ʽ�    
	string       f_forward_froz       ; //Զ�ڸ�������    
	string       f_exch_fare          ; //���׷���    �������ɽ��󣬸��ݳɽ������¼���Ľ���������
	string       s_variety_id         ; //Ʒ�ִ���    �D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D������
	string       s_curr_amt           ; //��ǰ���    
	string       s_can_use_amt        ; //���ÿ��    
	string       s_can_get_amt        ; //������    
	string       s_day_deposit        ; //�������    
	string       s_day_draw           ; //���ճ���    
	string       s_real_buy_amt       ; //�ɽ�����    
	string       s_real_sell_amt      ; //�ɽ�����    
	string       s_entr_sell_amt      ; //��������    
	string       s_app_froz_amt       ; //�������    
	string       s_unit_cost          ; //���ɱ�    
	string       t5_prod_code         ; //��Լ����    �D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�DԶ�ڲ�λ
	string       t5_long_amt          ; //��ǰ���    
	string       t5_short_amt         ; //��ǰ�ղ�    
	string       t5_can_use_long      ; //���ö��    
	string       t5_can_use_short     ; //���ÿղ�    
	string       t5_day_open_long     ; //���տ����    
	string       t5_day_open_short    ; //���տ��ղ�    
	string       td_prod_code         ; //��Լ����    �D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D���ڲ�λ
	string       td_long_amt          ; //��ǰ���    
	string       td_short_amt         ; //��ǰ�ղ�    
	string       td_can_use_long      ; //���ö��    
	string       td_can_use_short     ; //���ÿղ�    
	string       td_day_open_long     ; //���տ����    
	string       td_day_open_short    ; //���տ��ղ�    
	string       td_day_cov_long      ; //����ƽ���    
	string       td_day_cov_short     ; //����ƽ�ղ�    
	string       td_day_deli_long     ; //���ս�����    
	string       td_day_deli_short    ; //���ս���ղ�    
	string       td_day_cov_long_froz ; //����ƽ��ֶ���    
	string       td_day_cov_short_froz ; //����ƽ�ղֶ���    
	string       td_day_deli_long_forz ; //���ս����ֶ���    
	string       td_day_deli_short_forz ; //���ս���ղֶ���    
	string       td_long_open_avg_price ; //��ͷ���־���    
	string       td_short_open_avg_price ; //��ͷ���־���    
	string       td_long_posi_avg_price ; //��ͷ�ֲ־���    
	string       td_short_posi_avg_price ; //��ͷ�ֲ־���    
	string       td_long_margin       ; //��ͷ�ֱֲ�֤��    
	string       td_short_margin      ; //��ͷ�ֱֲ�֤��    
	string       td_last_settle_price ; //���ս����    
	string       td_day_settle_price  ; //���ս����    
	string       r_surplus            ; //����ӯ��    �D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�Dӯ����ѯ
	string       r_risk_index         ; //����ϵ��    
	string       r_risk_level         ; //���ռ���    
	HashtableMsg hlm_stor_info        ; //�����Ϣ�б�    �ֶΣ�29 �� 38
	HashtableMsg htm_t5_info          ; //Զ�ڳֲ���Ϣ�б�    �ֶΣ�39 �� 45
	HashtableMsg htm_td_info          ; //���ڳֲ���Ϣ�б�    �ֶΣ�46 �� 60

	HashtableMsg htm_prod_group_info;     //��������Ϣ
	HashtableMsg htm_acct_large_side_sum; //��߱�֤����Ϣ   

	void CopyCusInfo(const tagRsp1020& Other)
	{
		this->c_acct_no = Other.c_acct_no;
		this->c_account_no = Other.c_account_no;
		this->c_open_bank_name = Other.c_open_bank_name;
		this->c_cust_abbr = Other.c_cust_abbr;
		this->c_acct_stat = Other.c_acct_stat;
		this->c_branch_id = Other.c_branch_id;
	}

	void CopyFundInfo(const tagRsp1020& Other)
	{
		this->f_curr_bal = Other.f_curr_bal;
		this->f_can_use_bal = Other.f_can_use_bal;
		this->f_can_get_bal = Other.f_can_get_bal;
		this->f_exch_froz_bal = Other.f_exch_froz_bal;
		this->f_posi_margin = Other.f_posi_margin;
		this->f_base_margin = Other.f_base_margin;
		this->f_take_margin = Other.f_take_margin;
		this->f_stor_margin = Other.f_stor_margin;
		this->f_pt_reserve = Other.f_pt_reserve;
		this->f_ag_margin = Other.f_ag_margin;
	}

	void CopySurplus(const tagRsp1020& Other)
	{
		this->r_surplus = Other.r_surplus;
	}

}Rsp1020,*PRsp1020;

//----------------------------------------------Req���Ľӿ� [2022] ����
// �ṹ����:�˻������޸ĵ���������
typedef struct tagReq2022
{
	int          oper_flag            ; //������־    1�������޸�2��������������3���ʽ���������
	string       acct_no              ; //�ͻ���    
	string       acct_type            ; //�˻�����    
	string       old_exch_pwd         ; //ԭ��������    
	string       exch_pwd             ; //�½�������    
	string       old_fund_pwd         ; //ԭ�ʽ�����    
	string       fund_pwd             ; //���ʽ�����    
}Req2022,*PReq2022;


//----------------------------------------------Rsp���Ľӿ� [2022] ����
// �ṹ����:�˻������޸ĵ���Ӧ������
typedef struct tagRsp2022 : public RspBase
{
	int          oper_flag            ; //������־    1�������޸�2��������������3���ʽ���������
}Rsp2022,*PRsp2022;

//----------------------------------------------Req���Ľӿ� [2040] ����
// �ṹ����:�ͻ�ʵ�ʷ��ʲ�ѯ����������
typedef struct tagReq2040
{
	int          oper_flag            ; //������־    1. ��ѯ
	string       acct_no              ; //�ͻ���    
}Req2040,*PReq2040;


//----------------------------------------------Rsp���Ľӿ� [2040] ����
// �ṹ����:�ͻ�ʵ�ʷ��ʲ�ѯ����Ӧ������
typedef struct tagRsp2040 : public tagRspBase
{
	int          oper_flag            ; //������־    1. ��ѯ
	ArrayListMsg alm_b_fare_list      ; //�����������б�    �ֶ�Ϊ����Լ���룬��Լ�������ƣ��������ͣ������������ƣ��շ�ģʽ���շ�ģʽ���ƣ�����ֵ
	ArrayListMsg alm_m_fare_list      ; //��Ա�����б�    �ֶ�Ϊ����Լ���룬��Լ�������ƣ��������ͣ������������ƣ��շ�ģʽ���շ�ģʽ���ƣ�����ֵ,������Դ
}Rsp2040,*PRsp2040;

//----------------------------------------------Req���Ľӿ� [2201] ����
// �ṹ����:�սᵥȷ�ϵ���������
typedef struct tagReq2201
{
	int          oper_flag            ; //������־    1����ѯ2���սᵥȷ��
	string       acct_no              ; //�ͻ���    1*,2*
	string       affirm_date          ; //ȷ������    2*
}Req2201,*PReq2201;


//----------------------------------------------Rsp���Ľӿ� [2201] ����
// �ṹ����:�սᵥȷ�ϵ���Ӧ������
typedef struct tagRsp2201 : public tagRspBase
{
	int          oper_flag            ; //������־    1����ѯ2���սᵥȷ��
	string       affirm_date          ; //ȷ������    1*
}Rsp2201,*PRsp2201;

//----------------------------------------------Req���Ľӿ� [3021] ����
// �ṹ����:�Զ������ת�˵���������
typedef struct tagReq3010
{
	int          oper_flag            ; //������־    1����ѯ2��ת��3������ͨ��4�����˲�ͨ��
	string       serial_no            ; //������ˮ��    3*,4*
	string       acct_no              ; //�ͻ���    1,2*
	string       access_way           ; //��ȡ��־    1*,2* access_way
	double       exch_bal             ; //�������    2*
	string       remark               ; //��ע     2
	string       cust_id              ; //�ͻ�����    1
	string       cust_abbr            ; //�ͻ����    1
	string       branch_id            ; //�������    1
	string       c_status             ; //����״̬    2*
	string       o_teller_id          ; //�������Ա    2*
	string       account_no           ; //�����˺�
	string       open_bank_name       ; //��������    1
	string       fund_pwd             ; //�ʽ�����    3*,4*
}Req3010,*PReq3010;

//----------------------------------------------Rsp���Ľӿ� [3021] ����
// �ṹ����:�Զ������ת�˵���Ӧ������
typedef struct tagRsp3010 : public tagRspBase
{
	int          oper_flag            ; //������־    1����ѯ2��ת�� 3������ͨ��4�����˲�ͨ��
	string       serial_no              ; //
	string       acct_no              ; //
	string       cust_id              ; //
	string       cust_abbr              ; //
	string       acct_stat              ; //
	string       exec_name              ; //
	string       exec_cert_num              ; //
	double       curr_bal              ; //
	double       can_get_cash              ; //
	double       can_use_cash              ; //        (����)�ֶ�Ϊ��������ˮ��,�ͻ���,�ͻ����,��������������ʺ�,�������ƣ���ȡ����,�������,����״̬�������ˣ���������,����״̬,�Ƿ�������,��ע, 
	ArrayListMsg alm_custtype_list    ; //�����ʽ���ˮ�б�   �ֶ�Ϊ����ˮ�ţ��ͻ��ţ��ͻ���ƣ��˻�״̬�����ױ�־�������������˺ţ����������ƣ�����״̬�������ˣ��������ڣ������ˣ��������ڣ���ע		 
}Rsp3010,*PRsp3010;

//----------------------------------------------Req���Ľӿ� [3021] ����
// �ṹ����:�Զ������ת�˵���������
typedef struct tagReq3021
{
	int          oper_flag            ; //������־    1����ѯ2��ת��3������ͨ��4�����˲�ͨ��
	string       acct_no              ; //�ͻ���    1,2*
	string       access_way           ; //��ȡ��־    1*,2* access_way
	double       exch_bal             ; //�������    2*
	string       fund_pwd             ; //�ʽ�����    2*
	string       remark               ; //��ע     2
	string       cust_id              ; //�ͻ�����    1
	string       cust_abbr            ; //�ͻ����    1
	string       cust_type            ; //�ͻ����    1
	string       branch_id            ; //�������    1

	// �������������������ֶΣ������޸��ˣ�����֪��������������û��Ӱ�죬Ҫ�۲�
	string       card_pwd            ; //���п�����
	//string       serial_no            ; //������ˮ��
}Req3021,*PReq3021;

//----------------------------------------------Rsp���Ľӿ� [3021] ����
// �ṹ����:�Զ������ת�˵���Ӧ������
typedef struct tagRsp3021 : public tagRspBase
{
	int          oper_flag            ; //������־    1����ѯ2��ת�� 3������ͨ��4�����˲�ͨ��
	ArrayListMsg alm_custtype_list    ; //�����ʽ���ˮ�б�    �ֶ�Ϊ��������ˮ��,�ͻ���,�ͻ����,��������������ʺ�,�������ƣ���ȡ����,�������,����״̬�������ˣ���������,����״̬,�Ƿ�������,��ע, 
}Rsp3021,*PRsp3021;

typedef struct tagRep3024
{
	///<Sammary>
	/// ������־  1����ͨ		 
	///</Sammary>
	int oper_flag;

	///<Sammary>
	/// ���ױ���  1*		 
	///</Sammary>
	string acct_no;

	///<Sammary>
	/// ���д���  1*		 
	///</Sammary>
	string bank_no;

	///<Sammary>
	/// �̻���  1*		 
	///</Sammary>
	string bk_mer_code;

	///<Sammary>
	/// ���н��ױ���  		 
	///</Sammary>
	string bk_cust_no;

	///<Sammary>
	/// ���пͻ�����  		 
	///</Sammary>
	string bk_acct_name;

	///<Sammary>
	/// �����˺�  1*		 
	///</Sammary>
	string bk_acct_no;

	///<Sammary>
	/// ����֤�����  1*		 
	///</Sammary>
	string bk_cert_type;

	///<Sammary>
	/// ����֤������  1*		 
	///</Sammary>
	string bk_cert_no;

	///<Sammary>
	/// �Ƿ����֪ͨ  yes_no		 
	///</Sammary>
	string sms_flag;

	///<Sammary>
	/// �ֻ�����  ��ѡ(�������֪ͨ���ֻ��������)		 
	///</Sammary>
	string phone_num;

	///<Sammary>
	/// ��ע  ��ѡ		 
	///</Sammary>
	string remark;
}Rep3024,*PRep3024;

typedef struct tagRsp3024 : public tagRspBase
{
	///<Sammary>
	/// ������־  1����ѯ 2����ͨ 3��ȡ�� 4���޸�		 
	///</Sammary>
	int oper_flag;

	///<Sammary>
	/// �ͻ���  		 
	///</Sammary>
	string acct_no;

	///<Sammary>
	/// ���д���  		 
	///</Sammary>
	string bank_no;

	///<Sammary>
	/// �̻���  		 
	///</Sammary>
	string bk_mer_code;

	///<Sammary>
	/// ���пͻ���  		 
	///</Sammary>
	string bk_cust_no;

	///<Sammary>
	/// ���пͻ�����  		 
	///</Sammary>
	string bk_acct_name;

	///<Sammary>
	/// �����˺�  		 
	///</Sammary>
	string bk_acct_no;

	///<Sammary>
	/// ����֤�����  		 
	///</Sammary>
	string bk_cert_type;

	///<Sammary>
	/// ����֤������  		 
	///</Sammary>
	string bk_cert_no;

	///<Sammary>
	/// �Ƿ����֪ͨ  		 
	///</Sammary>
	string sms_flag;

	///<Sammary>
	/// �ֻ�����  		 
	///</Sammary>
	string phone_num;

	///<Sammary>
	/// ��ע  		 
	///</Sammary>
	string remark;
}Rsp3024,*PRsp3024;

//----------------------------------------------Req���Ľӿ� [3064] ����      ������ʾ��ѯ������������� 
typedef struct tagReq3064
{
	int oper_flag;                 // ������־    1����ѯ
	string branch_id;              // ����������
	string begin_time;             // ��ʼʱ��
	string end_time;               // ����ʱ��
	string acct_no;                // ���ױ���
	string tip_type;               // ��ʾ����    tip_type1��ʾ2׷��֪ͨ3ǿƽ֪ͨ
}Req3064,*PReq3064;
//�ṹ���壺������ʾ��ѯ�������Ӧ������ 
typedef struct tagRsp3064 : public tagRspBase
{
	int oper_flag;                  // ������־    1����ѯ
	ArrayListMsg alm_result;        // ��ѯ���    �ֶΣ�ʱ�䡢Դ���յȼ���Ŀ����յȼ������ױ��롢�ͻ���ơ��ͻ������˻����͡����ն�1�����ն�2��׷����֪ͨ���⡢֪ͨ���ݡ������̡������̼��
}Rsp3064,*PRsp3064;

//�ṹ���壺ǿƽ����ѯ���������� 
typedef struct tagReq3069
{
	int oper_flag;                 // ������־    1����ѯ
	string acct_no;                // ���ױ���
	string instid;                 // ��Լ����    
	string gene_type;              // ���ɷ�ʽ
	string begin_date;             // ��ʼ����  ָί������
	string end_date;               // ��������  ָί������
	ArrayListMsg order_status_set; // ����״̬ 

}Req3069,*PReq3069;
//�ṹ���壺ǿƽ����ѯ����Ӧ������ 
typedef struct tagRsp3069 : public tagRspBase
{
	int oper_flag;                  // ������־    1����ѯ
	ArrayListMsg order_status_set;  //��ѯ���    �ֶ�˳�򣺽��ױ���,�ͻ����,�ͻ�����,�˻�����,��Լ����,��������,ί�м۸�,ί������,ǿƽ����,����״̬,������,�ɽ�����,�ɽ�����,ǿƽ����Ա,��������Ա,ί��ʱ��,����ʱ��,�����̱��,�����̼��,���κ�,��ʱ�����ʽ�(���),��ʱ����ӯ��,��ʱ���ն�1,��ʱ���ն�2,��ʱ��Ա��֤��,��ʱ��������֤��,��ʱ�ܱ�֤��,��ʱ��Լ�۸�

}Rsp3069,*PRsp3069;

//----------------------------------------------Req���Ľӿ� [3099] ����      �ͻ����նȲ�ѯ����������
typedef struct tagReq3099
{
	int oper_flag;                 // ������־    1����ѯ
}Req3099,*PReq3099;
/*
�ṹ���壺�ͻ����նȲ�ѯ����Ӧ������ ��ȥ����risk_degree1��risk_degree2
���ݽ���ͨ����Ҫ�󣬻ָ�risk_degree1�Լ�risk_degree2����Ϊ����ͨ���õ���risk_degree2������ʱȥ��risk_degree 
*/
typedef struct tagRsp3099 : public tagRspBase
{
	int oper_flag;                  // ������־    1����ѯ
	string risk_degree1;            // ���ն�
	string risk_degree2;            // ���ն�
	string risk_grade;              // ���յȼ�
}Rsp3099,*PRsp3099;

//----------------------------------------------Req���Ľӿ� [3101] ����
// �ṹ����:��֤�𻮲�����������
typedef struct tagReq3101
{
	int          oper_flag            ; //������־    1������ת����ˮ��ѯ 2����ձ�֤����ˮ��ѯ3����ת����4���ٴη��� 5����ת��ѯ6����ձ�֤���ʲ�ѯ
	string       serial_no            ; //������ˮ��    3*
	string       acct_no              ; //�ͻ���    2*��1
	string       access_way           ; //��ȡ��־    2*��1
	double       exch_bal             ; //�������    2*
	string       remark               ; //��ע    
	string       fund_pwd             ; //�ʽ�����    2*
	string       branch_id            ; //�������    1
	string       grade_id             ; //�ͻ�����    1
	string       o_term_type          ; //������Դ    1 ��term_type 
	string       send_stat            ; //����״̬    1��b_send_stat 
}Req3101,*PReq3101;


//----------------------------------------------Rsp���Ľӿ� [3101] ����
// �ṹ����:��֤�𻮲�����Ӧ������
typedef struct tagRsp3101 : public tagRspBase
{
	int          oper_flag            ; //������־    1������ת����ˮ��ѯ 2����ձ�֤����ˮ��ѯ3����ת����4���ٴη��� 5����ת��ѯ6����ձ�֤���ʲ�ѯ
	string       Exch_date            ; //��������    
	string       Serial_no            ; //������ˮ��    
	string       Acct_no              ; //�ͻ���    
	string       bank_no              ; //���д���    
	string       f_busi_type          ; //ҵ������    
	string       access_way           ; //��ȡ����    
	string       out_account_no       ; //���������˺�    
	string       in_account_no        ; //��������˺�    
	string       Exch_bal             ; //�������    
	string       check_stat1          ; //����״̬1    
	string       check_stat2          ; //����״̬2    
	string       send_stat            ; //����״̬    
	string       in_account_flag      ; //�Ƿ�������    
	string       remark               ; //��ע    
	string       bk_plat_date         ; //��������    
	string       bk_seq_no            ; //������ˮ��    
	string       bk_rsp_code          ; //������Ӧ����    
	string       bk_rsp_msg           ; //������Ӧ��Ϣ    
	string       o_term_type          ; //������Դ    
	string       o_teller_id          ; //�����û���    
	string       o_date               ; //��������    
	string       c_term_type1         ; //����1��Դ    
	string       c_teller_id1         ; //����1�û���    
	string       c_date1              ; //����1����    
	string       c_term_type2         ; //����2��Դ    
	string       c_teller_id2         ; //����2�û���    
	string       c_date2              ; //����2���� 
	HashtableMsg htm_result           ; //��ѯ���    �ֶΣ�2-29
}Rsp3101,*PRsp3101;

//----------------------------------------------Req���Ľӿ� [3201] ����
// �ṹ����:��ѯ�ͻ������������
typedef struct tagReq3201
{
	int          oper_flag            ; // ������ʶ 1:��ѯ
	string       acct_no              ; // �ͻ���
}Req3201,*PReq3201;

typedef struct tagRsp3201 : public RspBase
{
	int    oper_flag;          // ������־    1����ѯ
	string card_bal;           // �����
}Rsp3201,*PRsp3201;

//----------------------------------------------Req���Ľӿ� [4001] ����
// �ṹ����:����ͳһ������
typedef struct tagReq4001
{
	string       oper_flag            ;//add by xiao
	string       client_serial_no     ; //�ͻ�����ˮ��    
	string       acct_no              ; //�ͻ���    
	string       cust_id              ; //�ͻ�����    
	string       bank_no              ; //���п���    
	string       b_market_id          ; //�����г�    b_market_id
	string       prod_code            ; //��Լ����    
	string       offset_flag          ; //��ƽ��־    b_offset_flag
	string       deli_flag            ; //���ձ�־    b_deli_flag
	string       bs                   ; //���׷���    b_buyorsell
	double       entr_price           ; //ί�м۸�    
	int          entr_amount          ; //ί������    
	string       cov_type             ; //ƽ�ַ�ʽ    cov_type
	string       match_type           ; //�ɽ�����    b_match_type
	string       src_match_no         ; //��λ���    ָ��ƽ�ֵ�ԭ�ɽ����
	string       order_send_type      ; //�������ͷ�ʽ    order_send_type
	string       auto_send_time_s     ; //�Զ����Ϳ�ʼʱ��    ��ʽ��HH24:MI:SS
	string       auto_send_time_e     ; //�Զ����ͽ���ʱ��    ��ʽ��HH24:MI:SS
	string       auto_send_stat_s     ; //Դ����״̬    B_INST_STAT
	string       auto_send_stat_t     ; //Ŀ�귢��״̬    B_INST_STAT
	string       auto_send_way        ; //�Զ����ͷ���    ORDER_SEND_WAY
	string       auto_send_comp       ; //�Զ����͹�ϵ    ORDER_SEND_COMP
	string       auto_send_price      ; //�Զ����ͼ۸�    
	string       order_type           ; //��������
}Req4001,*PReq4001;

//----------------------------------------------Rsp���Ľӿ� [4001] ����
// �ṹ����:����ͳһ������
typedef struct tagRsp4001 : public tagRspBase
{
	string       client_serial_no     ; //�ͻ�����ˮ��    
	string       local_order_no       ; //���ر�����    
}Rsp4001,*PRsp4001;


//----------------------------------------------Req���Ľӿ� [4061] ����
// �ṹ����:���׳���
typedef struct tagReq4061
{
	int          oper_flag            ; //������־    1�����׳��� 
	string       cancel_order_no      ; //������������    
}Req4061,*PReq4061;

//----------------------------------------------Rsp���Ľӿ� [4061] ����
// �ṹ����:���׳���
typedef struct tagRsp4061 : public tagRspBase
{
	int          oper_flag            ; //������־    1�����׳��� 
}Rsp4061,*PRsp4061;


//----------------------------------------------Req���Ľӿ� [4071] ����
// �ṹ����:ƽ�������������
typedef struct tagReq4071
{
	int          oper_flag            ; //������־    1��ƽ������ 
	string       acct_no              ; //�ͻ���    
	string       prod_code            ; //��Լ����    
	string       cov_bs               ; //ƽ�ַ���    b:ƽ�ղ�s:ƽ���
	string       cov_price            ; //ƽ�ּ۸�    
	int          cov_amount           ; //ƽ������    
}Req4071,*PReq4071;

//----------------------------------------------Rsp���Ľӿ� [4071] ����
// �ṹ����:ƽ���������Ӧ����
typedef struct tagRsp4071 : public tagRspBase
{
	int          oper_flag            ; //������־    1��ƽ������ 
	string       acct_no              ; //�ͻ���    
	string       cust_abbr            ; //�ͻ����    
	string       prod_code            ; //��Լ����    
	string       remain_long          ; //���ʣ������    
	string       remain_short         ; //�ղ�ʣ������    
	string       cov_exch_fare        ; //ƽ��������    
	string       cov_surplus          ; //ƽ��ӯ��    
	string       can_use_bal          ; //���ý��   
}Rsp4071,*PRsp4071;


//----------------------------------------------Req���Ľӿ� [5041] ����
// �ṹ����:���������ά������������
typedef struct tagReq5041
{
	int          oper_flag            ; //������־    1����ѯ2���޸�
	string       year                 ; //���ѡ��    
	string       branch_id            ; //�������    1*
	string       is_search_usefull    ; //�Ƿ��ѯ��ǰ������֮�������    yes_no
	string       search_num           ; //��ѯ�����������¼    
	ArrayListMsg alm_take_sheet_date  ; //������б�    �ֶ�Ϊ����������
}Req5041,*PReq5041;

//----------------------------------------------Rsp���Ľӿ� [5041] ����
// �ṹ����:���������ά������Ӧ������
typedef struct tagRsp5041 : public tagRspBase
{
	int          oper_flag            ; //������־    1����ѯ2���޸�
	string       year                 ; //���ѡ��    
	string       branch_id            ; //�������   
	ArrayListMsg alm_take_sheet_date  ; //������б�    �ֶ�Ϊ����������
}Rsp5041,*PRsp5041;


//----------------------------------------------Req���Ľӿ� [5101] ����
// �ṹ����:���ӿڵ����������ˮά������������
typedef struct tagReq5101
{
	int          oper_flag            ; //������־    1. ��ѯ2. �������3. ������볷��4��������ȷ��
	string       local_sheet_no       ; //������������    
	string       sheet_no             ; //��������    
	string       acct_no              ; //�ͻ���    
	string       cust_id              ; //�ͻ�����    
	string       variety_id           ; //����Ʒ�ִ���    
	string       app_amount           ; //�����׼����    
	string       city_code            ; //�������    
	string       stor_id              ; //�ֿ����    
	string       take_man             ; //�����    
	string       cert_type_id         ; //�����֤������    
	string       cert_num             ; //�����֤������    
	string       app_pwd              ; //�������    
	string       app_record           ; //����¼����    
	string       take_date            ; //Ԥ�������    
	string       start_date           ; //���뽻����ʼ����    8λ���ڱ�ʾ����ѯ��
	string       end_date             ; //���뽻�׽�������    8λ���ڱ�ʾ����ѯ��
}Req5101,*PReq5101;


//----------------------------------------------Rsp���Ľӿ� [5101] ����
// �ṹ����:���������ˮ��ѯ����Ӧ������
typedef struct tagRsp5101 : public tagRspBase
{
	int          oper_flag            ; //������־    1. ��ѯ2. �������3. ������볷��
	string       local_sheet_no       ; //������������    
	string       sheet_no             ; //��������    
	string       acct_no              ; //�ͻ���    
	string       cust_id              ; //�ͻ�����    
	string       variety_id           ; //����Ʒ�ִ���    
	string       app_amount           ; //�����׼����    
	string       draw_type            ; //�������    
	string       self_draw            ; //��������    
	string       trade_draw           ; //��������    
	string       city_code            ; //�������    
	string       stor_id              ; //�ֿ����    
	string       take_man             ; //�����    
	string       cert_type_id         ; //�����֤������    
	string       cert_num             ; //�����֤������    
	string       app_record           ; //����¼����    
	string       app_date             ; //������������    
	string       app_time             ; //����ʱ��    
	string       app_exch_date        ; //���뽻������    
	string       app_start_date       ; //���������ʼ����    
	string       app_end_date         ; //���������ֹ����    
	string       due_take_date        ; //Ԥ�������    
	string       stat                 ; //���״̬    b_sheet_stat
	string       cancel_date          ; //������������    
	string       cancel_time          ; //����ʱ��    
	string       cancel_exch_date     ; //������������    
	string       cancel_record        ; //����¼����    
	string       send_stat            ; //����״̬    
	string       take_margin          ; //�����֤��    
	string       is_other_take        ; //�Ƿ�������    yes_no
	string       take_affirm          ; //������ȷ��    yes_no      
	HashtableMsg htm_take_sheet_detail ; //���������ˮ�б�    �ֶΣ�2--31
}Rsp5101,*PRsp5101;

//----------------------------------------------Req���Ľӿ� [5103] ����
// �ṹ����:�������ӡ������
typedef struct tagReq5103
{
	int          oper_flag            ; //������־    1. ��ѯ
	string       local_sheet_no       ; //������������    
	string       sheet_no             ; //��������    
	string       acct_no              ; //�ͻ���    
	string       cust_id              ; //�ͻ�����    
	string       start_date           ; //���뽻����ʼ����    8λ���ڱ�ʾ����ѯ��
	string       end_date             ; //���뽻�׽�������    8λ���ڱ�ʾ����ѯ��
}Req5103,*PReq5103;


//----------------------------------------------Rsp���Ľӿ� [5103] ����
// �ṹ����:�������ӡ��Ӧ����
typedef struct tagRsp5103 : public tagRspBase
{
	int          oper_flag            ; //������־    1. ��ѯ2.������ȷ��
	ArrayListMsg alm_take_sheet_detail ; //���������ˮ�б�    ������������,��������,�ͻ���,�ͻ�����,�ͻ�����,��Ա����,��Ա����,�����Ա����,����Ʒ�ִ���,�����׼����,�������,��������,��������,�������,�ֿ����,�ֿ�����,�ֿ��ַ,�ֿ���ϵ��,�ֿ���ϵ�绰,�����,�����֤������,�����֤������,���뽻������,���������ʼ����,���������ֹ����,���״̬,����״̬,�Ƿ�������,������ȷ��,��Ӧ����,��Ӧ��Ϣ
}Rsp5103,*PRsp5103;

//----------------------------------------------Req���Ľӿ� [6001] ����
// �ṹ����:��ѯ�������ò�ѯ
typedef struct tagReq6001
{
	int          oper_flag            ; //������־    1����ѯ
	string       query_id             ; //��ѯ��ʶ    
}Req6001,*PReq6001;


//----------------------------------------------Rsp���Ľӿ� [6001] ����
// �ṹ����:��ѯ�������ò�ѯ����Ӧ������
typedef struct tagRsp6001 : public RspBase
{
	int          oper_flag            ; //������־    1����ѯ
	string       query_id             ; //��ѯ��ʶ    
	string       query_name           ; //��ѯ����    
	int          cell_num             ; //ÿ������    
	int          cell_inv_width       ; //��ѯ�������Ҽ��    
	int          cell_inv_height      ; //��ѯ�������¼��    
	ArrayListMsg alm_options          ; //��ѯ����    ������ʶ|Ĭ��ֵ|�ؼ�����|��ȱ���|^
	ArrayListMsg alm_field_en_name    ; //��ѯ���Ӣ���ֶ�����    
	ArrayListMsg alm_field_cn_name    ; //��ѯ��������ֶ�����    
	ArrayListMsg alm_field_width      ; //��ѯ����п��    
	ArrayListMsg alm_field_align      ; //��ѯ����ж��뷽ʽ    1�������2������ 3���Ҷ���
	ArrayListMsg alm_field_format     ; //��ѯ�����ʽ��    
}Rsp6001,*PRsp6001;



//----------------------------------------------Req���Ľӿ� [6002] ����
// �ṹ����:��ͨ��ѯ
typedef struct tagReq6002
{
	int          oper_flag            ; //������־    1����ѯ
	string       login_branch_id      ; //��¼�ߴ��������    
	string       login_teller_id      ; //��¼�߲���Ա��    
	int          paginal_num          ; //ÿҳ��¼��    
	int          curr_page            ; //��ǰ��ѯҳ    
	string       query_id             ; //��ѯ��ʶ    
	ArrayListMsg alm_view_field       ; //��ʾ�ֶ�    ��ǰ��ѯ��Ҫ��ʾ���ֶ�
}Req6002,*PReq6002;


//----------------------------------------------Rsp���Ľӿ� [6002] ����
// �ṹ����:��ͨ��ѯ
typedef struct tagRsp6002 : public tagRspBase
{
	int          oper_flag            ; //������־    1����ѯ
	int          paginal_num          ; //ÿҳ��¼��    
	int          page_count           ; //�����ҳ��    
	int          curr_page            ; //��ǰ��ѯҳ  
	ArrayListMsg alm_result           ; //��ѯ���    
}Rsp6002,*PRsp6002;

//----------------------------------------------Req���Ľӿ� [6005] ����
// �ṹ����:�����������ò�ѯ����������
typedef struct tagReq6005
{
	int          oper_flag            ; //������־    1����ѯ
	string       report_id            ; //�����ʶ    1*
	string       c_rdlc_ver           ; //�ͻ��˸�ʽ�ļ��汾��    1*
}Req6005,*PReq6005;


//----------------------------------------------Rsp���Ľӿ� [6005] ����
// �ṹ����:�����������ò�ѯ����Ӧ������
typedef struct tagRsp6005 : public RspBase
{
	int          oper_flag            ; //������־    1����ѯ
	string       report_id            ; //�����ʶ    
	string       report_name          ; //��������    
	int          cell_num             ; //ÿ������    
	int          cell_inv_width       ; //�����������Ҽ��    
	int          cell_inv_height      ; //�����������¼��    
	string       s_rdlc_ver           ; //��������ʽ�ļ��汾��    
	//string       rsp_m;
	ArrayListMsg alm_data_source      ; //����Դ�б�    �ֶ�˳������Դ����
	ArrayListMsg alm_options          ; //��������    �ֶ�˳��������ʶ,Ĭ��ֵ,�ؼ�����,��ȱ���
}Rsp6005,*PRsp6005;

//----------------------------------------------Req���Ľӿ� [6007] ����
// �ṹ����:����Դ���ص���������
typedef struct tagReq6007
{
	int          oper_flag            ; //������־    1������Դ����
	string       exch_date            ; //Add by xiaorensong
	ArrayListMsg alm_ds_list          ; //����Դ�б�    
}Req6007,*PReq6007;


//----------------------------------------------Rsp���Ľӿ� [6007] ����
// �ṹ����:����Դ���ص���Ӧ������
typedef struct tagRsp6007 : public tagRspBase
{
	int          oper_flag            ; //������־    1������Դ����
	HashtableMsg htm_Title   ;//
	HashtableMsg htm_AcctSettleRisk   ;//
	HashtableMsg htm_AcctSettleFund   ;//
	HashtableMsg htm_AcctSettleFundDetail   ;//
	HashtableMsg htm_AcctSettleStorage   ;//
	HashtableMsg htm_AcctSettleForward   ;//
	HashtableMsg htm_AcctSettleDefer   ;//
	HashtableMsg htm_AcctSettleSurplus   ;//
	HashtableMsg htm_AcctSettleMatchFlow   ;//
	HashtableMsg htm_AcctSettleFundInOutFlow   ;//
}Rsp6007,*PRsp6007;

//----------------------------------------------Req���Ľӿ� [8001] ����
// �ṹ����:�û���¼
typedef struct tagReq8001
{
	int          oper_flag            ; //������־    1���û���¼
	string       user_type            ; //�û�����    user_type
	string       user_id_type         ; //�û�ID����    ����¼�û�Ϊ�ͻ�ʱ����ֵ��Ч��1���ͻ���2�������˺�
	string       user_id              ; //�û�ID    
	string       user_pwd             ; //�û�����    
	string       login_ip             ; //��¼IP    
	string       ver_num              ; //�ͻ��˰汾��    
	string       is_down_para         ; //�Ƿ����ز�����Ϣ    ����ͻ��˵İ汾����������˵����°汾�Ų�һ�£�ǿ�����ء���Ӧ���ĵ��ֶ�20��ʼ
	string       bank_no              ; //���д���    ���ͻ�ʹ�á������˺š���¼ʱ����ֵ����
	string       login_server_code    ; //����������    �ͻ���ǰ����ҵ��ʹ�õķ���������

	string       isSign               ; // �Ƿ�ǩ��
	string       CN                   ; // ǩ���ļ�CN�� issignΪ��ʱ,����
	string		 session_id			  ;//add lqh 2014.3.10
}Req8001,*PReq8001;


//----------------------------------------------Rsp���Ľӿ� [8001] ����
// �ṹ����:�û���¼��Ӧ������
typedef struct tagRsp8001 : public tagRspBase
{
	int          oper_flag            ; //������־    1���û���¼
	string       check_code           ; //У����    
	string       member_id            ; //��Ա���    �ͻ���¼ʱ��ֵ
	string       member_name          ; //��Ա����    �ͻ���¼ʱ��ֵ
	string       branch_id            ; //��������������    
	string       branch_name          ; //���������������    
	string       acct_type            ; //�˻�����    �ͻ���¼ʱ��ֵ
	string       user_id              ; //�û�ID    
	string       user_name            ; //�û�����    
	string       sys_date             ; //ϵͳ����    
	string       exch_date            ; //��������    
	string       exch_time            ; //����ʱ��    
	string       last_exch_date       ; //�ϸ���������    
	string       version              ; //�������汾��    
	string       m_sys_stat           ; //����ϵͳ״̬    M_SYS_STAT
	string       b_sys_stat           ; //������ϵͳ״̬    B_SYS_STAT
	string       first_login          ; //�Ƿ��״ε�¼    yes_no
	string       need_change_pwd      ; //�Ƿ�����޸�����    yes_no
	string       last_login_date      ; //�ϴε�¼����    
	string       last_login_time      ; //�ϴε�¼ʱ��    
	string       last_lan_ip          ; //�ϴε�¼����IP    
	string       last_www_ip          ; //�ϴε�¼����IP    ��ʱ��ֵ
	string       exist_login          ; //�Ƿ��ѵ�¼    
	int          no_affirm_rpt_num    ; //�սᵥδȷ������    �ͻ���¼ʱ��ֵ
	string       comp_stat            ; //�ͻ��˰汾�������    1����¼�ͻ���Ϊ���°棬���ظ��£�2��ϵͳ�����µĿͻ��˰汾������Ŀǰ��¼�ͻ��ˣ����ݻ����£�3��ϵͳ�����µĿͻ��˰汾������ӪĿǰ��¼�ͻ��ˣ�������¡�
	string auto_entry_menu_id         ;
	string		more_login_msg		;		//������ʾ����¼��ʷ��¼��¼
	ArrayListMsg alm_menu_info        ; //��Ȩ�����Ĳ˵�    
	ArrayListMsg alm_cust_type_id     ; //�����ͻ�����    �ͻ���¼ʱ��ֵ�ֶΣ��ͻ�����ID
	ArrayListMsg alm_take_man_list    ; //������б�    �ֶΣ������������֤�����ͣ�֤������
	ArrayListMsg alm_role_list        ; //����Ա������ɫ�б�    �ֶΣ���ɫID
	ArrayListMsg alm_code_table_list  ; //����б�    �ֶΣ�������ƣ����ID���������
	ArrayListMsg alm_prod_code_list   ; //��Լ�����б�    �ֶΣ���Լ���룬��Լ���ƣ�Ʒ����𣬽���Ʒ�ִ��룬��С�䶯��λ����ͣ���ʣ���ͣ���ʣ���Ծ��־�����׵�λ��������λ�������г�
	ArrayListMsg alm_variety_list     ; //����Ʒ���б�    �ֶΣ�����Ʒ�ִ��룬����Ʒ��ȫ�ƣ���ƣ�Ʒ�������С������������������������λ��ע����־
	ArrayListMsg alm_city_code_list   ; //���д����б�    �ֶΣ����д��룬�������ƣ�ӵ������ֿ⣬Ĭ������ֿ�
	ArrayListMsg alm_fare_type_list   ; //���������б�    �ֶΣ���������ID���������ͷ��࣬�����������������õĺ�Լ���룬
	ArrayListMsg alm_query_list       ; //��ѯ�����б�    �ֶμ������˵��
	ArrayListMsg alm_report_list      ; //���������б�    �ֶμ������˵��
	ArrayListMsg alm_noread_bulletin_list ; //δ�������б�    �ֶΣ�������š��������
}Rsp8001,*PRsp8001;



//----------------------------------------------Req���Ľӿ� [8002] ����
// �ṹ����:�û��˳�
typedef struct tagReq8002
{
	int          oper_flag            ; //������־    1���û��˳�
	string       user_type            ; //�û�����    user_type
	string       user_id              ; //�û�ID    
	string       session_id           ; //�ỰID    
}Req8002,*PReq8002;


//----------------------------------------------Rsp���Ľӿ� [8002] ����
// �ṹ����:�û���¼��Ӧ������
typedef struct tagRsp8002 : public tagRspBase
{
	int          oper_flag            ; //������־    1���û��˳�
}Rsp8002,*PRsp8002;

//----------------------------------------------Req���Ľӿ� [8006] ����
// �ṹ����:��¼��֤
typedef struct tagReq8006
{
	int          oper_flag            ; //������־    1����¼��֤
	string       user_type            ; //�û�����    user_type
	string       user_id_type         ; //�û�ID����    ����¼�û�Ϊ�ͻ�ʱ����ֵ��Ч��1���ͻ���2�������˺�
	string       user_id              ; //�û�ID    
	string       user_pwd             ; //�û�����    
	string       login_ip             ; //��¼IP    
	string       bank_no              ; //���д���    ���ͻ�ʹ�á������˺š���¼ʱ����ֵ����
	string       net_envionment       ; //���绷��    net_envionment
	string       net_agent            ; //������Ӫ��    net_agent
	string       isSign               ; // add for ����ͨ
}Req8006,*PReq8006;


//----------------------------------------------Rsp���Ľӿ� [8006] ����
// �ṹ����:��¼��֤
typedef struct tagRsp8006 : public tagRspBase
{
	int          oper_flag            ; //������־    1����¼��֤
	string       session_id           ; //�ỰID    
	string       session_key          ; //�Ự��Կ    
	string       server_code          ; //����������    
	string       server_name          ; //����������    
	string       trans_ip             ; //���׷����ַ    
	int          trans_port           ; //���׷���˿�    
	string       query_ip             ; //��ѯ�����ַ    
	int          query_port           ; //��ѯ����˿�    
	string       broadcast_ip         ; //��Ѷ�����ַ    
	int          broadcast_port       ; //��Ѷ����˿�    
	string       risk_trans_ip        ; //��ؽ��׷����ַ    
	int          risk_trans_port      ; //��ؽ��׷���˿�    
	string       risk_broadcast_ip    ; //��ع㲥�����ַ    
	int          risk_broadcast_port  ; //��ع㲥����˿�    
	HashtableMsg htm_server_list      ; //���������б�    �ֶΣ�4-15
	ArrayListMsg htm_more_login_list;	//����¼���� ,lqh 2014-3-6 10:45:36 for GF
}Rsp8006,*PRsp8006;

//----------------------------------------------Req���Ľӿ�[8007] ����
// �ṹ����:��Ļ����
typedef struct tagReq8007
{
	int          oper_flag            ; //������־    1����¼��֤
	string       user_type            ; //�û�����    user_type
	string       user_id_type         ; //�û�ID����    ����¼�û�Ϊ�ͻ�ʱ����ֵ��Ч��1���ͻ���2�������˺�
	string       user_id              ; //�û�ID    
	string       user_pwd             ; //�û�����    
	string       login_ip             ; //��¼IP    
	string       bank_no              ; //���д���    ���ͻ�ʹ�á������˺š���¼ʱ����ֵ����
	string       isSign               ; // add for ����ͨ
}Req8007,*PReq8007;

//----------------------------------------------Rsp���Ľӿ� [8007] ����
// �ṹ����:��Ļ����
typedef struct tagRsp8007 : public RspBase
{
	int          oper_flag            ; //������־    1����������
	string       succ                 ; //���ܳɹ�    yes_no
}Rsp8007,*PRsp8007;


//----------------------------------------------Req���Ľӿ� [8030] ����
// �ṹ����:�����������ѯ����������
typedef struct tagReq8030
{
	int          oper_flag            ; //������־    1����ѯ 
	string       seq_no               ; //�������    
	string       title                ; //�������    ��ģ��ƥ��
	string       s_exch_date          ; //��ʼ��������    
	string       e_exch_date          ; //������������    
}Req8030,*PReq8030;

//----------------------------------------------Rsp���Ľӿ� [8030] ����
// �ṹ����:�����������ѯ����Ӧ������
typedef struct tagRsp8030 : public RspBase
{
	int          oper_flag            ; //������־    1����ѯ 
	ArrayListMsg alm_result           ; //��ѯ���    �ֶ�˳����š����⡢���ݡ������ˡ��������ڡ�����ʱ��
}Rsp8030,*PRsp8030;


//----------------------------------------------Req���Ľӿ� [8031] ����
// �ṹ����:��Ա�����ѯ����������
typedef struct tagReq8031
{
	int          oper_flag            ; //������־    1����ѯ 
	string       bulletin_id          ; //�������    
	string       title                ; //�������    ��ģ��ƥ��
	string       s_exch_date          ; //��ʼ��������    
	string       e_exch_date          ; //������������    
}Req8031,*PReq8031;


//----------------------------------------------Rsp���Ľӿ� [8031] ����
// �ṹ����:��Ա�����ѯ����Ӧ������
typedef struct tagRsp8031 : public tagRspBase
{
	int          oper_flag            ; //������־    1����ѯ 
	ArrayListMsg alm_result           ; //��ѯ���    �ֶ�˳����š����⡢���ݡ������ˡ�����ʱ��
}Rsp8031,*PRsp8031;

//----------------------------------------------Req���Ľӿ� [9010] ����
// �ṹ����:���������ѯ����������
typedef struct tagReq9010
{
	int          oper_flag            ; //������־    1����ѯ�¼�2����ѯ�ϼ�
	string       branch_id            ; //����������    
	string       is_contain_self      ; //�Ƿ��������    
	string       bank_no              ; //���д���    
}Req9010,*PReq9010;


//----------------------------------------------Rsp���Ľӿ� [9010] ����
// �ṹ����:���������ѯ����Ӧ������
typedef struct tagRsp9010 : public tagRspBase
{
	int          oper_flag            ; //������־    1����ѯ�¼�2����ѯ�ϼ�
	string       branch_id            ; //����������    
	string       branch_name          ; //�����������    
	string       branch_level         ; //�����������    
	string       parent_branch_id     ; //�ϼ��������    
	string       bank_no              ; //���д���    
	string       city_code            ; //��������    
	string       is_self_bank         ; //�Ƿ��л���   
	HashtableMsg htm_branch_info      ; //��������б�    �ֶΣ� 2-8
}Rsp9010,*PRsp9010;


//----------------------------------------------Req���Ľӿ� [9030] ����
// �ṹ����:ϵͳ����������������
typedef struct tagReq4074
{
	int          oper_flag            ; //������־    1����ѯ 2������ 3���޸� 4��ɾ�� 
	string       start_date              ; //��ʼ����  
	string       end_date            ; //��������    
	string       acct_no            ; //�ͻ���    
	string       delegate_type           ; //ί������   
	string       src_match_no           ; // ԭ�ɽ���ˮ��
	string       trigger_status           ; // ����״̬
	string       serial_no           ; // �й���ˮ��
	string       exch_type           ; // ���״���
	string       prod_code           ; // ��Լ����
	double       entr_price           ; // ί�м۸�
	int       entr_amount           ; // ί������
	string       entr_price_type           ; // ����������
	string       trigger_condition           ; // ��������
	string       trigger_value_type           ; // ����ֵ����
	string       trigger_value           ; // ����ֵ
	int       base_adjust_step           ; // ��׼�۵�����λ
	int       entr_adjust_step           ; // �����۵�����λ

	tagReq4074()
	{
		base_adjust_step = 0;
		entr_adjust_step = 0;
		entr_price = 0.00;
	}
}Req4074,*PReq4074;

typedef struct tagRsp4074 : public RspBase
{
	int          oper_flag            ; //������־    1����ѯ 2������ 3���޸� 4��ɾ��
	ArrayListMsg       alm_result              ; /*�ֶΣ�
												 �й���ˮ��(0),��������(1),�ͻ���(2),ί������(3),���״���(4),��Լ����(5),
												 ί�м۸�(6),ί������(7),��������(8),��������(9),����ֵ(10),
												 ��׼�۵�����λ(11),�����۵�����λ(12),����״̬(13),����ʱ��(14),ί����Դ(15),
												 ί�в���Ա(16),ί��ʱ��(17),�޸���Դ(18),�޸Ĳ���Ա(19),����޸�ʱ��(20),
												 ������Դ(21),��������Ա(22),����ʱ��(23)   
												 */
}Rsp4074,*PRsp4074;


//----------------------------------------------Req���Ľӿ� [9030] ����
// �ṹ����:ϵͳ����������������
typedef struct tagReq9030
{
	int          oper_flag            ; //������־    1����ѯ 2������ 3���޸� 4��ɾ�� 
	string       para_id              ; //����ID    
	string       para_type            ; //��������    
	string       para_desc            ; //��������    
	string       para_value           ; //����ֵ    
}Req9030,*PReq9030;


//----------------------------------------------Rsp���Ľӿ� [9030] ����
// �ṹ����:ϵͳ����������Ӧ������
typedef struct tagRsp9030 : public tagRspBase
{
	int          oper_flag            ; //������־    1����ѯ 2������ 3���޸� 4��ɾ��
	string       para_id              ; //����ID    
	string       para_type            ; //��������    
	string       para_desc            ; //��������    
	string       para_value           ; //����ֵ    
	HashtableMsg htm_para_info        ; //���ײ����б�    �ֶ�Ϊ������ID���������ͣ���������������ֵ
}Rsp9030,*PRsp9030;

#ifdef RUN_EMULATOR
// 
typedef struct tagReq3999
{
	int          oper_flag            ; // ������־  1����ѯ��� 2����ѯ��ˮ 
	string       acct_no              ; // �ͻ���   
	string       trans_type           ; // ҵ������  0������ 1����� 4������    
	string       in_flag              ; // ���ʱ�־  0��δ���� 1��������    
	string       start_date           ; // ��ʼ����    
	string       end_date             ; // ��������   
}Req3999,*PReq3999;
typedef struct tagRsp3999 : public tagRspBase
{
	int          oper_flag            ; // ������־  1����ѯ��� 2����ѯ��ˮ
	string       balance              ; // ��� 
	ArrayListMsg alm_flow             ; // ��ˮ��Ϣ  �ֶ�Ϊ���������ڣ�������ˮ�ţ��ͻ����룬�����˺ţ�ҵ�����ͣ��������Ƿ������ʣ���ע���������ڣ�������ˮ��
}Rsp3999,*PRsp3999;

// 
typedef struct tagReq5999
{
	int          oper_flag            ; // ������־  1����ѯ 2������  
	string       acct_no              ; // �ͻ���   
	string       variety_id           ; // ����Ʒ��    
	string       amount               ; // ����   
}Req5999,*PReq5999;
typedef struct tagRsp5999 : public tagRspBase
{
	int          oper_flag            ; // ������־  1����ѯ 2������
	ArrayListMsg alm_flow             ; // ��ˮ��Ϣ  �ֶ�Ϊ���ͻ��ţ�����Ʒ�֣�����
}Rsp5999,*PRsp5999;

// �����޸ĵ���������
typedef struct tagReq2997
{
	int          oper_flag            ; // ������־  1�������޸� 2����ѯ�ͻ���Ϣ  
	string       acct_no              ; // �ͻ���   
	string       cust_name            ; // �ͻ�����    
	string       fax                  ; // ������� 
	string       zipcode              ; // �������� 
	string       address              ; // ��ϵ��ַ 
	string       email                ; // ���� 
	string       qq                   ; // QQ 
	string       msn                  ; // MSN 
}Req2997,*PReq2997;
typedef struct tagRsp2997 : public tagRspBase
{
	int          oper_flag            ; // ������־  1�������޸� 2����ѯ�ͻ���Ϣ
	string       cust_name            ; // �ͻ�����
	string       fax                  ; // �������
	string       zipcode              ; // ��������
	string       address              ; // ��ϵ��ַ
	string       email                ; // ����
	string       qq                   ; // QQ
	string       msn                  ; // MSN
}Rsp2997,*PRsp2997;

// �ֻ��ű������������
typedef struct tagReq2996
{
	int          oper_flag            ; // ������־  1����ѯ�ͻ����� 2���ֻ��ű��
	string       acct_no              ; // �ͻ���   
	string       question1            ; // ����1    
	string       answer1              ; // ��1 
	string       question2            ; // ����2 
	string       answer2              ; // ��2 
	string       new_mobile           ; // ���ֻ��� 
}Req2996,*PReq2996;
// �ֻ��ű������Ӧ������
typedef struct tagRsp2996 : public tagRspBase
{
	int          oper_flag            ; // ������־  1����ѯ�ͻ����� 2���ֻ��ű��
	string       question_id1         ; // ����1���
	string       question_content1    ; // ����1����
	string       question_id2         ; // ����2���
	string       question_content2    ; // ����2����
}Rsp2996,*PRsp2996;

// ���������������������
typedef struct tagReq2995
{
	int          oper_flag            ; // ������־  1����ѯ 2�������������
	string       acct_no              ; // �ͻ���   
	string       question1            ; // ����1    
	string       answer1              ; // ��1 
	string       question2            ; // ����2 
	string       answer2              ; // ��2 
	string       new_branch_id        ; // ���������� 
}Req2995,*PReq2995;
// �ֻ��ű������Ӧ������
typedef struct tagRsp2995 : public tagRspBase
{
	int          oper_flag            ; // ������־  1����ѯ�ͻ����� 2���ֻ��ű��
	string       question_id1         ; // ����1���
	string       question_content1    ; // ����1����
	string       question_id2         ; // ����2���
	string       question_content2    ; // ����2����
	ArrayListMsg alm_branch_info      ; // ��������б�  �ֶ�Ϊ�����������ţ�����������ƣ������������
}Rsp2995,*PRsp2995;

// �ָ���ʼ״̬����������
typedef struct tagReq2994
{
	int          oper_flag            ; // ������־  1���ָ���ʼ״̬
	string       acct_no              ; // �ͻ���   
}Req2994,*PReq2994;
typedef struct tagRsp2994 : public tagRspBase
{
	int          oper_flag            ; // ������־  1���ָ���ʼ״̬
}Rsp2994,*PRsp2994;

// �����֤����������
typedef struct tagReq8999
{
	int          oper_flag            ; // ������־  1����ѯ�ͻ����� 2����ѯ�ͻ���Ϣ 3��ȷ��
	string       acct_no              ; // �ͻ���   
	string       question1            ; // ����1    
	string       answer1              ; // ��1 
	string       question2            ; // ����2 
	string       answer2              ; // ��2 
	string       cert_type_id         ; // ֤������
	string       cert_num             ; // ֤������
	string       cust_name            ; // �ͻ�����
	string       addr                 ; // ͨѶ��ַ
	string       zip_code             ; // �ʱ�
}Req8999,*PReq8999;
typedef struct tagRsp8999 : public tagRspBase
{
	int          oper_flag            ; // ������־  1����ѯ�ͻ����� 2����ѯ�ͻ���Ϣ 3��ȷ��
 
	string       question_id1         ; // ����1���
	string       question_content1    ; // ����1����
	string       question_id2         ; // ����2���
	string       question_content2    ; // ����2����

	string       cert_type_id         ; // ֤������
	string       cert_num             ; // ֤������
	string       cust_name            ; // �ͻ�����
	string       addr                 ; // ͨѶ��ַ
	string       zipcode             ; // �ʱ�
}Rsp8999,*PRsp8999;

// ������������������
typedef struct tagReq8998
{
	int          oper_flag            ; // ������־  1���ָ���ʼ״̬
	string       acct_no              ; // �ͻ���   
	string       match_no             ; // �������
}Req8998,*PReq8998;
typedef struct tagRsp8998 : public tagRspBase
{
	int          oper_flag            ; // ������־  1���ָ���ʼ״̬
	ArrayListMsg alm_match_info       ; // ������Ϣ�б�  �ֶ�Ϊ��������ţ�������ƣ�����ȫ�ƣ��ٰ�����������ʼ�ʽ𣬻���������˵����������ʼ���ڣ������������ڣ�������ʼ���ڣ������������ڣ���С���׽���С���״���������״̬����ע
}Rsp8998,*PRsp8998;

// �����˳�����������
typedef struct tagReq8997
{
	int          oper_flag            ; // ������־  1���ָ���ʼ״̬
	string       acct_no              ; // �ͻ���   
	string       match_no             ; // �������
}Req8997,*PReq8997;
typedef struct tagRsp8997 : public tagRspBase
{
	int          oper_flag            ; // ������־  1���ָ���ʼ״̬
	string       match_no             ; // �������
	string       match_abbr           ; // �������
	string       match_name           ; // ����ȫ��
	string       branch_id            ; // �ٰ�������
	string       init_fund            ; // ��ʼ�ʽ�
	string       win_peoples          ; // ������
	string       win_show             ; // ��˵��
	string       start_join_date      ; // ������ʼ����
	string       end_join_date        ; // ������������
	string       start_match_date     ; // ������ʼ����
	string       end_match_date       ; // ������������
	string       min_exch_bal         ; // ��С���׽��
	string       min_exch_count       ; // ��С���״���
	string       stat                 ; // ����״̬
	string       memo                 ; // ��ע
}Rsp8997,*PRsp8997;

// �������������ѯ����������
typedef struct tagReq8897
{
	int          oper_flag            ; // ������־  1����ѯ
	string       branch_id            ; // �������   
}Req8897,*PReq8897;
typedef struct tagRsp8897 : public tagRspBase
{
	int          oper_flag            ; // ������־  1����ѯ
	ArrayListMsg alm_match_info       ; // ������Ϣ�б�  �ֶ�Ϊ��������ţ��������
}Rsp8897,*PRsp8897;

// �������õ���������
typedef struct tagReq2998
{
	int          oper_flag            ; // ������־  1����ѯ�ͻ����� 2�������������� 3���ʽ���������		
	string       question1            ; // ����1    
	string       answer1              ; // ��1 
	string       question2            ; // ����2 
	string       answer2              ; // ��2 
	string       mobile_phone         ; // �ֻ��� 
	string       new_password         ; // ������   
}Req2998,*PReq2998;
typedef struct tagRsp2998 : public tagRspBase
{
	int          oper_flag            ; // ������־  1����ѯ�ͻ����� 2�������������� 3���ʽ���������	
	string       question_id1         ; // ����1���
	string       question_content1    ; // ����1����
	string       question_id2         ; // ����2���
	string       question_content2    ; // ����2����
}Rsp2998,*PRsp2998;

// �¿ͻ�ע�����������
typedef struct tagReq2999
{
	int          oper_flag            ; // ������־  1��ע��ǰ��ѯ 2���¿ͻ�ע�� 3����ȡ�ֻ���֤��		
	string       acct_no              ; // �ͻ�����
	string       cust_name            ; // �ͻ�����
	string       sex                  ; // �ͻ��Ա�  1���� 2��Ů
	string       mobile_phone         ; // �ֻ���
	string       verify_code          ; // �ֻ���֤��
	string       account_no           ; // ���п���
	string       cert_type_id         ; // ֤������
	string       cert_num             ; // ֤������
	string       branch_id            ; // �������
	string       zipcode              ; // ��������
	string       addr                 ; // ��ϵ��ַ
	string       email                ; // ����
	string       qq                   ; // QQ
	string       msn                  ; // MSN
	string       fax                  ; // ����
	string       exch_pwd             ; // ��������
	string       fund_pwd             ; // �ʽ�����
	string       question1            ; // ����1
	string       answer1              ; // ��1
	string       question2            ; // ����2
	string       answer2              ; // ��2
	string       question3            ; // ����3
	string       answer3              ; // ��3
	string       question4            ; // ����4
	string       answer4              ; // ��4
	string       question5            ; // ����5
	string       answer5              ; // ��5
	string       bank_no              ; // ���д���
}Req2999,*PReq2999;
typedef struct tagRsp2999 : public tagRspBase
{
	int          oper_flag            ; // ������־  1��ע��ǰ��ѯ 2���¿ͻ�ע�� 3����ȡ�ֻ���֤��		
	string       acct_no              ; // �ͻ�����
	string       is_verify            ; // �Ƿ���Ҫ�ֻ���֤
	ArrayListMsg    alm_branch_info   ; // ��������б�  �ֶ�Ϊ�����������ţ�����������ƣ������������
	ArrayListMsg    alm_question      ; // �����б�  �ֶ�Ϊ�������ţ���������
}Rsp2999,*PRsp2999;

#endif

class CTradePacketAndStruct
{
public:

#ifdef RUN_EMULATOR
	// ���Ľ����� �ṹ -> ����    ����ȡ����������
	static int Struct2Packet(Req3999& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        , stBody.oper_flag);
		pkt.AddParameter("acct_no"          , stBody.acct_no);
		pkt.AddParameter("trans_type"       , stBody.trans_type);
		pkt.AddParameter("in_flag"          , stBody.in_flag);
		pkt.AddParameter("start_date"       , stBody.start_date);
		pkt.AddParameter("end_date"         , stBody.end_date);

		return 0;
	};
	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp3999& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"       , stBody.oper_flag);
		pkt.GetParameterVal("balance"         , stBody.balance);
		pkt.GetParameterVal("alm_flow"        , stBody.alm_flow);

		return 0;
	};


	// ���Ľ����� �ṹ -> ����    ����ȡ����������
	static int Struct2Packet(Req5999& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        , stBody.oper_flag);
		pkt.AddParameter("acct_no"          , stBody.acct_no);
		pkt.AddParameter("variety_id"       , stBody.variety_id);
		pkt.AddParameter("amount"           , stBody.amount);

		return 0;
	};
	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp5999& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"       , stBody.oper_flag);
		pkt.GetParameterVal("alm_flow"         , stBody.alm_flow);
		Packet2StructBase(stBody, pkt);

		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����������
	static int Struct2Packet(Req2997& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        , stBody.oper_flag);
		pkt.AddParameter("acct_no"          , stBody.acct_no);
		pkt.AddParameter("cust_name"        , stBody.cust_name);
		pkt.AddParameter("fax"              , stBody.fax);
		pkt.AddParameter("zipcode"          , stBody.zipcode);
		pkt.AddParameter("address"          , stBody.address);
		pkt.AddParameter("email"            , stBody.email);
		pkt.AddParameter("qq"               , stBody.qq);
		pkt.AddParameter("msn"              , stBody.msn);

		return 0;
	};
	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp2997& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"       , stBody.oper_flag);
		pkt.GetParameterVal("cust_name"       , stBody.cust_name);
		pkt.GetParameterVal("fax"             , stBody.fax);
		pkt.GetParameterVal("zipcode"         , stBody.zipcode);
		pkt.GetParameterVal("address"         , stBody.address);
		pkt.GetParameterVal("email"           , stBody.email);
		pkt.GetParameterVal("qq"              , stBody.qq);
		pkt.GetParameterVal("msn"             , stBody.msn);

		Packet2StructBase(stBody, pkt);

		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����������
	static int Struct2Packet(Req2996& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        , stBody.oper_flag);
		pkt.AddParameter("acct_no"          , stBody.acct_no);
		pkt.AddParameter("question1"        , stBody.question1);
		pkt.AddParameter("answer1"          , stBody.answer1);
		pkt.AddParameter("question2"        , stBody.question2);
		pkt.AddParameter("answer2"          , stBody.answer2);
		pkt.AddParameter("new_mobile"       , stBody.new_mobile);

		return 0;
	};
	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp2996& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"          , stBody.oper_flag);
		pkt.GetParameterVal("question_id1"       , stBody.question_id1);
		pkt.GetParameterVal("question_content1"  , stBody.question_content1);
		pkt.GetParameterVal("question_id2"       , stBody.question_id2);
		pkt.GetParameterVal("question_content2"  , stBody.question_content2);

		Packet2StructBase(stBody, pkt);

		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����������
	static int Struct2Packet(Req2995& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        , stBody.oper_flag);
		pkt.AddParameter("acct_no"          , stBody.acct_no);
		pkt.AddParameter("question1"        , stBody.question1);
		pkt.AddParameter("answer1"          , stBody.answer1);
		pkt.AddParameter("question2"        , stBody.question2);
		pkt.AddParameter("answer2"          , stBody.answer2);
		pkt.AddParameter("new_branch_id"    , stBody.new_branch_id);

		return 0;
	};
	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp2995& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"          , stBody.oper_flag);
		pkt.GetParameterVal("question_id1"       , stBody.question_id1);
		pkt.GetParameterVal("question_content1"  , stBody.question_content1);
		pkt.GetParameterVal("question_id2"       , stBody.question_id2);
		pkt.GetParameterVal("question_content2"  , stBody.question_content2);
		pkt.GetParameterVal("alm_branch_info"    , stBody.alm_branch_info);

		Packet2StructBase(stBody, pkt);

		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����������
	static int Struct2Packet(Req2994& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        , stBody.oper_flag);
		pkt.AddParameter("acct_no"          , stBody.acct_no);

		return 0;
	};
	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp2994& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"          , stBody.oper_flag);
		Packet2StructBase(stBody, pkt);

		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����������
	static int Struct2Packet(Req8999& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        , stBody.oper_flag);
		pkt.AddParameter("acct_no"          , stBody.acct_no);
		pkt.AddParameter("question1"        , stBody.question1);
		pkt.AddParameter("answer1"          , stBody.answer1);
		pkt.AddParameter("question2"        , stBody.question2);
		pkt.AddParameter("answer2"          , stBody.answer2);
		pkt.AddParameter("cert_type_id"     , stBody.cert_type_id);
		pkt.AddParameter("cert_num"         , stBody.cert_num);
		pkt.AddParameter("cust_name"        , stBody.cust_name);
		pkt.AddParameter("addr"             , stBody.addr);
		pkt.AddParameter("zip_code"         , stBody.zip_code);

		return 0;
	};
	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp8999& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"           , stBody.oper_flag);
		pkt.GetParameterVal("question_id1"        , stBody.question_id1);
		pkt.GetParameterVal("question_content1"   , stBody.question_content1);
		pkt.GetParameterVal("question_id2"        , stBody.question_id2);
		pkt.GetParameterVal("question_content2"   , stBody.question_content2);
		pkt.GetParameterVal("cert_type_id"        , stBody.cert_type_id);
		pkt.GetParameterVal("cert_num"            , stBody.cert_num);
		pkt.GetParameterVal("cust_name"           , stBody.cust_name);
		pkt.GetParameterVal("addr"                , stBody.addr);
		pkt.GetParameterVal("zipcode"             , stBody.zipcode);

		Packet2StructBase(stBody, pkt);

		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����������
	static int Struct2Packet(Req8998& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        , stBody.oper_flag);
		pkt.AddParameter("acct_no"          , stBody.acct_no);
		pkt.AddParameter("match_no"          , stBody.match_no);

		return 0;
	};
	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp8998& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"          , stBody.oper_flag);
		pkt.GetParameterVal("alm_match_info"     , stBody.alm_match_info);
		Packet2StructBase(stBody, pkt);

		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����������
	static int Struct2Packet(Req8997& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        , stBody.oper_flag);
		pkt.AddParameter("acct_no"          , stBody.acct_no);
		pkt.AddParameter("match_no"          , stBody.match_no);

		return 0;
	};
	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp8997& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"          , stBody.oper_flag);
		pkt.GetParameterVal("match_no"           , stBody.match_no);
		pkt.GetParameterVal("match_abbr"         , stBody.match_abbr);
		pkt.GetParameterVal("match_name"         , stBody.match_name);
		pkt.GetParameterVal("branch_id"          , stBody.branch_id);
		pkt.GetParameterVal("init_fund"          , stBody.init_fund);
		pkt.GetParameterVal("win_peoples"        , stBody.win_peoples);
		pkt.GetParameterVal("win_show"           , stBody.win_show);
		pkt.GetParameterVal("start_join_date"    , stBody.start_join_date);
		pkt.GetParameterVal("end_join_date"      , stBody.end_join_date);
		pkt.GetParameterVal("start_match_date"   , stBody.start_match_date);
		pkt.GetParameterVal("end_match_date"     , stBody.end_match_date);
		pkt.GetParameterVal("min_exch_bal"       , stBody.min_exch_bal);
		pkt.GetParameterVal("min_exch_count"     , stBody.min_exch_count);
		pkt.GetParameterVal("stat"               , stBody.stat);
		pkt.GetParameterVal("memo"               , stBody.memo);

		Packet2StructBase(stBody, pkt);

		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����������
	static int Struct2Packet(Req8897& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        , stBody.oper_flag);
		pkt.AddParameter("branch_id"          , stBody.branch_id);

		return 0;
	};
	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp8897& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"          , stBody.oper_flag);
		pkt.GetParameterVal("alm_match_info"     , stBody.alm_match_info);
		Packet2StructBase(stBody, pkt);

		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����������
	static int Struct2Packet(Req2998& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        , stBody.oper_flag);
		pkt.AddParameter("question1"        , stBody.question1);
		pkt.AddParameter("answer1"          , stBody.answer1);
		pkt.AddParameter("question2"        , stBody.question2);
		pkt.AddParameter("answer2"          , stBody.answer2);
		pkt.AddParameter("mobile_phone"       , stBody.mobile_phone);
		pkt.AddParameter("new_password"          , stBody.new_password);

		return 0;
	};
	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp2998& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"          , stBody.oper_flag);
		pkt.GetParameterVal("question_id1"       , stBody.question_id1);
		pkt.GetParameterVal("question_content1"  , stBody.question_content1);
		pkt.GetParameterVal("question_id2"       , stBody.question_id2);
		pkt.GetParameterVal("question_content2"  , stBody.question_content2);

		Packet2StructBase(stBody, pkt);

		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����������
	static int Struct2Packet(Req2999& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        , stBody.oper_flag);
		pkt.AddParameter("acct_no"          , stBody.acct_no);
		pkt.AddParameter("cust_name"        , stBody.cust_name);
		pkt.AddParameter("sex"              , stBody.sex);
		pkt.AddParameter("mobile_phone"     , stBody.mobile_phone);
		pkt.AddParameter("verify_code"      , stBody.verify_code);
		pkt.AddParameter("account_no"       , stBody.account_no);
		pkt.AddParameter("cert_type_id"     , stBody.cert_type_id);
		pkt.AddParameter("cert_num"         , stBody.cert_num);
		pkt.AddParameter("branch_id"        , stBody.branch_id);
		pkt.AddParameter("zipcode"          , stBody.zipcode);
		pkt.AddParameter("addr"             , stBody.addr);
		pkt.AddParameter("email"            , stBody.email);
		pkt.AddParameter("qq"               , stBody.qq);
		pkt.AddParameter("msn"              , stBody.msn);
		pkt.AddParameter("fax"              , stBody.fax);
		pkt.AddParameter("exch_pwd"         , stBody.exch_pwd);
		pkt.AddParameter("fund_pwd"         , stBody.fund_pwd);
		pkt.AddParameter("question1"        , stBody.question1);
		pkt.AddParameter("answer1"          , stBody.answer1);
		pkt.AddParameter("question2"        , stBody.question2);
		pkt.AddParameter("answer2"          , stBody.answer2);
		pkt.AddParameter("question3"        , stBody.question3);
		pkt.AddParameter("answer3"          , stBody.answer3);
		pkt.AddParameter("question4"        , stBody.question4);
		pkt.AddParameter("answer4"          , stBody.answer4);
		pkt.AddParameter("question5"        , stBody.question5);
		pkt.AddParameter("answer5"          , stBody.answer5);
		pkt.AddParameter("bank_no"          , stBody.bank_no);

		return 0;
	};
	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp2999& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"          , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"       , stBody.acct_no);
		pkt.GetParameterVal("is_verify"  , stBody.is_verify);
		pkt.GetParameterVal("alm_branch_info"       , stBody.alm_branch_info);
		pkt.GetParameterVal("alm_question"  , stBody.alm_question);

		Packet2StructBase(stBody, pkt);

		return 0;
	};


#endif

	// ���Ľ��������� -> �ṹ 
	static int Packet2Struct(RspBase& stBody, CTradePacket& pkt)
	{
		return 0;
	};

	// ���Ľ��������� -> �ṹ 
	static int Packet2StructBase(RspBase& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("rsp_msg"         , stBody.rsp_msg);

		return 0;
	};


	// ���Ľ��������� -> �ṹ    ����ȡ����������
	static int Packet2Struct(Req1001& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("code_type"         , stBody.code_type);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����������
	static int Struct2Packet(Req1001& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("code_type"         , stBody.code_type);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp1001& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("code_type"         , stBody.code_type);
		pkt.GetParameterVal("code_id"           , stBody.code_id);
		pkt.GetParameterVal("code_desc"         , stBody.code_desc);
		pkt.GetParameterVal("htm_code_list"     , stBody.htm_code_list);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����Ӧ������
	static int Struct2Packet(Rsp1001& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("code_type"         , stBody.code_type);
		pkt.AddParameter("code_id"           , stBody.code_id);
		pkt.AddParameter("code_desc"         , stBody.code_desc);
		pkt.AddParameter("htm_code_list"     , stBody.htm_code_list);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ��Լ�����趨
	static int Packet2Struct(Req1002& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("prod_code"         , stBody.prod_code);
		pkt.GetParameterVal("prod_name"         , stBody.prod_name);
		pkt.GetParameterVal("variety_type"      , stBody.variety_type);
		pkt.GetParameterVal("variety_id"        , stBody.variety_id);
		pkt.GetParameterVal("tick"              , stBody.tick);
		pkt.GetParameterVal("upper_limit_value" , stBody.upper_limit_value);
		pkt.GetParameterVal("lower_limit_value" , stBody.lower_limit_value);
		pkt.GetParameterVal("active_flag"       , stBody.active_flag);
		pkt.GetParameterVal("exch_unit"         , stBody.exch_unit);
		pkt.GetParameterVal("measure_unit"      , stBody.measure_unit);
		pkt.GetParameterVal("market_id"         , stBody.market_id);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ��Լ�����趨
	static int Struct2Packet(Req1002& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("prod_code"         , stBody.prod_code);
		pkt.AddParameter("prod_name"         , stBody.prod_name);
		pkt.AddParameter("variety_type"      , stBody.variety_type);
		pkt.AddParameter("variety_id"        , stBody.variety_id);
		pkt.AddParameter("tick"              , stBody.tick);
		pkt.AddParameter("upper_limit_value" , stBody.upper_limit_value);
		pkt.AddParameter("lower_limit_value" , stBody.lower_limit_value);
		pkt.AddParameter("active_flag"       , stBody.active_flag);
		pkt.AddParameter("exch_unit"         , stBody.exch_unit);
		pkt.AddParameter("measure_unit"      , stBody.measure_unit);
		pkt.AddParameter("market_id"         , stBody.market_id);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ��Լ�����趨
	static int Packet2Struct(Rsp1002& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("prod_code"         , stBody.prod_code);
		pkt.GetParameterVal("prod_name"         , stBody.prod_name);
		pkt.GetParameterVal("variety_type"      , stBody.variety_type);
		pkt.GetParameterVal("variety_id"        , stBody.variety_id);
		pkt.GetParameterVal("tick"              , stBody.tick);
		pkt.GetParameterVal("upper_limit_value" , stBody.upper_limit_value);
		pkt.GetParameterVal("lower_limit_value" , stBody.lower_limit_value);
		pkt.GetParameterVal("active_flag"       , stBody.active_flag);
		pkt.GetParameterVal("exch_unit"         , stBody.exch_unit);
		pkt.GetParameterVal("measure_unit"      , stBody.measure_unit);
		pkt.GetParameterVal("market_id"         , stBody.market_id);
		pkt.GetParameterVal("htm_prod_code"     , stBody.htm_prod_code);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ��Լ�����趨
	static int Struct2Packet(Rsp1002& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("prod_code"         , stBody.prod_code);
		pkt.AddParameter("prod_name"         , stBody.prod_name);
		pkt.AddParameter("variety_type"      , stBody.variety_type);
		pkt.AddParameter("variety_id"        , stBody.variety_id);
		pkt.AddParameter("tick"              , stBody.tick);
		pkt.AddParameter("upper_limit_value" , stBody.upper_limit_value);
		pkt.AddParameter("lower_limit_value" , stBody.lower_limit_value);
		pkt.AddParameter("active_flag"       , stBody.active_flag);
		pkt.AddParameter("exch_unit"         , stBody.exch_unit);
		pkt.AddParameter("measure_unit"      , stBody.measure_unit);
		pkt.AddParameter("market_id"         , stBody.market_id);
		pkt.AddParameter("htm_prod_code"     , stBody.htm_prod_code);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ����Ʒ���趨
	static int Packet2Struct(Req1004& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("variety_id"        , stBody.variety_id);
		pkt.GetParameterVal("name"              , stBody.name);
		pkt.GetParameterVal("abbr"              , stBody.abbr);
		pkt.GetParameterVal("variety_type"      , stBody.variety_type);
		pkt.GetParameterVal("min_pickup"        , stBody.min_pickup);
		pkt.GetParameterVal("pickup_base"       , stBody.pickup_base);
		pkt.GetParameterVal("weight_unit"       , stBody.weight_unit);
		pkt.GetParameterVal("destroy_flag"      , stBody.destroy_flag);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����Ʒ���趨
	static int Struct2Packet(Req1004& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("variety_id"        , stBody.variety_id);
		pkt.AddParameter("name"              , stBody.name);
		pkt.AddParameter("abbr"              , stBody.abbr);
		pkt.AddParameter("variety_type"      , stBody.variety_type);
		pkt.AddParameter("min_pickup"        , stBody.min_pickup);
		pkt.AddParameter("pickup_base"       , stBody.pickup_base);
		pkt.AddParameter("weight_unit"       , stBody.weight_unit);
		pkt.AddParameter("destroy_flag"      , stBody.destroy_flag);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ����Ʒ���趨
	static int Packet2Struct(Rsp1004& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("variety_id"        , stBody.variety_id);
		pkt.GetParameterVal("name"              , stBody.name);
		pkt.GetParameterVal("abbr"              , stBody.abbr);
		pkt.GetParameterVal("variety_type"      , stBody.variety_type);
		pkt.GetParameterVal("min_pickup"        , stBody.min_pickup);
		pkt.GetParameterVal("pickup_base"       , stBody.pickup_base);
		pkt.GetParameterVal("weight_unit"       , stBody.weight_unit);
		pkt.GetParameterVal("destroy_flag"      , stBody.destroy_flag);
		pkt.GetParameterVal("htm_variety_list"  , stBody.htm_variety_list);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����Ʒ���趨
	static int Struct2Packet(Rsp1004& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("variety_id"        , stBody.variety_id);
		pkt.AddParameter("name"              , stBody.name);
		pkt.AddParameter("abbr"              , stBody.abbr);
		pkt.AddParameter("variety_type"      , stBody.variety_type);
		pkt.AddParameter("min_pickup"        , stBody.min_pickup);
		pkt.AddParameter("pickup_base"       , stBody.pickup_base);
		pkt.AddParameter("weight_unit"       , stBody.weight_unit);
		pkt.AddParameter("destroy_flag"      , stBody.destroy_flag);
		pkt.AddParameter("htm_variety_list"  , stBody.htm_variety_list);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    �������Ʒ���趨
	static int Packet2Struct(Req1005& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("prod_code"         , stBody.prod_code);
		pkt.GetParameterVal("seq_no"            , stBody.seq_no);
		pkt.GetParameterVal("variety_id"        , stBody.variety_id);
		pkt.GetParameterVal("diff_amt"          , stBody.diff_amt);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �������Ʒ���趨
	static int Struct2Packet(Req1005& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("prod_code"         , stBody.prod_code);
		pkt.AddParameter("seq_no"            , stBody.seq_no);
		pkt.AddParameter("variety_id"        , stBody.variety_id);
		pkt.AddParameter("diff_amt"          , stBody.diff_amt);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    �������Ʒ���趨
	static int Packet2Struct(Rsp1005& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("prod_code"         , stBody.prod_code);
		pkt.GetParameterVal("seq_no"            , stBody.seq_no);
		pkt.GetParameterVal("variety_id"        , stBody.variety_id);
		pkt.GetParameterVal("diff_amt"          , stBody.diff_amt);
		pkt.GetParameterVal("htm_variety_info"  , stBody.htm_variety_info);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �������Ʒ���趨
	static int Struct2Packet(Rsp1005& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("prod_code"         , stBody.prod_code);
		pkt.AddParameter("seq_no"            , stBody.seq_no);
		pkt.AddParameter("variety_id"        , stBody.variety_id);
		pkt.AddParameter("diff_amt"          , stBody.diff_amt);
		pkt.AddParameter("htm_variety_info"  , stBody.htm_variety_info);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    �ֿ���Ϣά��
	static int Packet2Struct(Req1006& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("stor_id  "         , stBody.stor_id  );
		pkt.GetParameterVal("stor_name"         , stBody.stor_name);
		pkt.GetParameterVal("addr     "         , stBody.addr     );
		pkt.GetParameterVal("tel      "         , stBody.tel      );
		pkt.GetParameterVal("fax      "         , stBody.fax      );
		pkt.GetParameterVal("link_man "         , stBody.link_man );
		pkt.GetParameterVal("zip_code "         , stBody.zip_code );
		pkt.GetParameterVal("use_variety_type"  , stBody.use_variety_type);
		pkt.GetParameterVal("is_take"           , stBody.is_take);
		pkt.GetParameterVal("city_code"         , stBody.city_code);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �ֿ���Ϣά��
	static int Struct2Packet(Req1006& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("stor_id  "         , stBody.stor_id  );
		pkt.AddParameter("stor_name"         , stBody.stor_name);
		pkt.AddParameter("addr     "         , stBody.addr     );
		pkt.AddParameter("tel      "         , stBody.tel      );
		pkt.AddParameter("fax      "         , stBody.fax      );
		pkt.AddParameter("link_man "         , stBody.link_man );
		pkt.AddParameter("zip_code "         , stBody.zip_code );
		pkt.AddParameter("use_variety_type"  , stBody.use_variety_type);
		pkt.AddParameter("is_take"           , stBody.is_take);
		pkt.AddParameter("city_code"         , stBody.city_code);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    �ֿ���Ϣά��
	static int Packet2Struct(Rsp1006& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("stor_id  "         , stBody.stor_id  );
		pkt.GetParameterVal("stor_name"         , stBody.stor_name);
		pkt.GetParameterVal("addr     "         , stBody.addr     );
		pkt.GetParameterVal("tel      "         , stBody.tel      );
		pkt.GetParameterVal("fax      "         , stBody.fax      );
		pkt.GetParameterVal("link_man "         , stBody.link_man );
		pkt.GetParameterVal("zip_code "         , stBody.zip_code );
		pkt.GetParameterVal("use_variety_type"  , stBody.use_variety_type);
		pkt.GetParameterVal("is_take"           , stBody.is_take);
		pkt.GetParameterVal("city_code"         , stBody.city_code);
		pkt.GetParameterVal("htm_stor_info"     , stBody.htm_stor_info);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �ֿ���Ϣά��
	static int Struct2Packet(Rsp1006& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("stor_id  "         , stBody.stor_id  );
		pkt.AddParameter("stor_name"         , stBody.stor_name);
		pkt.AddParameter("addr     "         , stBody.addr     );
		pkt.AddParameter("tel      "         , stBody.tel      );
		pkt.AddParameter("fax      "         , stBody.fax      );
		pkt.AddParameter("link_man "         , stBody.link_man );
		pkt.AddParameter("zip_code "         , stBody.zip_code );
		pkt.AddParameter("use_variety_type"  , stBody.use_variety_type);
		pkt.AddParameter("is_take"           , stBody.is_take);
		pkt.AddParameter("city_code"         , stBody.city_code);
		pkt.AddParameter("htm_stor_info"     , stBody.htm_stor_info);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ���д���ά������������
	static int Packet2Struct(Req1007& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("city_code"         , stBody.city_code);
		pkt.GetParameterVal("city_name"         , stBody.city_name);
		pkt.GetParameterVal("all_stor_id"       , stBody.all_stor_id);
		pkt.GetParameterVal("stor_id_default"   , stBody.stor_id_default);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ���д���ά������������
	static int Struct2Packet(Req1007& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("city_code"         , stBody.city_code);
		pkt.AddParameter("city_name"         , stBody.city_name);
		pkt.AddParameter("all_stor_id"       , stBody.all_stor_id);
		pkt.AddParameter("stor_id_default"   , stBody.stor_id_default);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp1007& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("city_code"         , stBody.city_code);
		pkt.GetParameterVal("city_name"         , stBody.city_name);
		pkt.GetParameterVal("all_stor_id"       , stBody.all_stor_id);
		pkt.GetParameterVal("stor_id_default"   , stBody.stor_id_default);
		pkt.GetParameterVal("htm_code_list"     , stBody.htm_code_list);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����Ӧ������
	static int Struct2Packet(Rsp1007& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("city_code"         , stBody.city_code);
		pkt.AddParameter("city_name"         , stBody.city_name);
		pkt.AddParameter("all_stor_id"       , stBody.all_stor_id);
		pkt.AddParameter("stor_id_default"   , stBody.stor_id_default);
		pkt.AddParameter("htm_code_list"     , stBody.htm_code_list);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    �ͻ��ۺ���Ϣ��ѯ
	static int Packet2Struct(Req1020& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("qry_cust_info"     , stBody.qry_cust_info);
		pkt.GetParameterVal("qry_fund"          , stBody.qry_fund);
		pkt.GetParameterVal("qry_storage"       , stBody.qry_storage);
		pkt.GetParameterVal("qry_forward"       , stBody.qry_forward);
		pkt.GetParameterVal("qry_defer"         , stBody.qry_defer);
		pkt.GetParameterVal("qry_surplus"       , stBody.qry_surplus);
		pkt.GetParameterVal("is_check_stat"     , stBody.is_check_stat);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �ͻ��ۺ���Ϣ��ѯ
	static int Struct2Packet(Req1020& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("qry_cust_info"     , stBody.qry_cust_info);
		pkt.AddParameter("qry_fund"          , stBody.qry_fund);
		pkt.AddParameter("qry_storage"       , stBody.qry_storage);
		pkt.AddParameter("qry_forward"       , stBody.qry_forward);
		pkt.AddParameter("qry_defer"         , stBody.qry_defer);
		pkt.AddParameter("qry_surplus"       , stBody.qry_surplus);
		pkt.AddParameter("is_check_stat"     , stBody.is_check_stat);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    �ͻ��ۺ���Ϣ��ѯ
	static int Packet2Struct(Rsp1020& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("c_acct_no"         , stBody.c_acct_no);
		pkt.GetParameterVal("c_cust_id"         , stBody.c_cust_id);
		pkt.GetParameterVal("c_account_no"      , stBody.c_account_no);
		pkt.GetParameterVal("c_open_bank_name"  , stBody.c_open_bank_name);
		pkt.GetParameterVal("c_cust_abbr"       , stBody.c_cust_abbr);
		pkt.GetParameterVal("c_b_fare_model_id" , stBody.c_b_fare_model_id);
		pkt.GetParameterVal("c_m_fare_model_id" , stBody.c_m_fare_model_id);
		pkt.GetParameterVal("c_acct_type"       , stBody.c_acct_type);
		pkt.GetParameterVal("c_ocma_flag"       , stBody.c_ocma_flag);
		pkt.GetParameterVal("c_acct_stat"       , stBody.c_acct_stat);
		pkt.GetParameterVal("c_broker_acct_no"  , stBody.c_broker_acct_no);
		pkt.GetParameterVal("c_cert_type"       , stBody.c_cert_type);
		pkt.GetParameterVal("c_cert_num"        , stBody.c_cert_num);
		pkt.GetParameterVal("c_branch_id"       , stBody.c_branch_id);
		pkt.GetParameterVal("c_trans_check_info", stBody.c_trans_check_info);
		pkt.GetParameterVal("f_currency_id"     , stBody.f_currency_id);
		pkt.GetParameterVal("f_curr_bal"        , stBody.f_curr_bal);
		pkt.GetParameterVal("f_can_use_bal"     , stBody.f_can_use_bal);
		pkt.GetParameterVal("f_can_get_bal"     , stBody.f_can_get_bal);
		pkt.GetParameterVal("f_in_bal"          , stBody.f_in_bal);
		pkt.GetParameterVal("f_out_bal"         , stBody.f_out_bal);
		pkt.GetParameterVal("f_buy_bal"         , stBody.f_buy_bal);
		pkt.GetParameterVal("f_sell_bal"        , stBody.f_sell_bal);
		pkt.GetParameterVal("f_exch_froz_bal"   , stBody.f_exch_froz_bal);
		pkt.GetParameterVal("f_posi_margin"     , stBody.f_posi_margin);
		pkt.GetParameterVal("f_base_margin"     , stBody.f_base_margin);
		pkt.GetParameterVal("f_take_margin"     , stBody.f_take_margin);
		pkt.GetParameterVal("f_stor_margin"     , stBody.f_stor_margin);
		pkt.GetParameterVal("f_pt_reserve"      , stBody.f_pt_reserve);
		pkt.GetParameterVal("f_ag_margin"       , stBody.f_ag_margin);
		pkt.GetParameterVal("f_forward_froz"    , stBody.f_forward_froz);
		pkt.GetParameterVal("f_exch_fare"       , stBody.f_exch_fare);
		pkt.GetParameterVal("s_variety_id"      , stBody.s_variety_id);
		pkt.GetParameterVal("s_curr_amt"        , stBody.s_curr_amt);
		pkt.GetParameterVal("s_can_use_amt"     , stBody.s_can_use_amt);
		pkt.GetParameterVal("s_can_get_amt"     , stBody.s_can_get_amt);
		pkt.GetParameterVal("s_day_deposit"     , stBody.s_day_deposit);
		pkt.GetParameterVal("s_day_draw"        , stBody.s_day_draw);
		pkt.GetParameterVal("s_real_buy_amt"    , stBody.s_real_buy_amt);
		pkt.GetParameterVal("s_real_sell_amt"   , stBody.s_real_sell_amt);
		pkt.GetParameterVal("s_entr_sell_amt"   , stBody.s_entr_sell_amt);
		pkt.GetParameterVal("s_app_froz_amt"    , stBody.s_app_froz_amt);
		pkt.GetParameterVal("s_unit_cost"       , stBody.s_unit_cost);
		pkt.GetParameterVal("t5_prod_code"      , stBody.t5_prod_code);
		pkt.GetParameterVal("t5_long_amt"       , stBody.t5_long_amt);
		pkt.GetParameterVal("t5_short_amt"      , stBody.t5_short_amt);
		pkt.GetParameterVal("t5_can_use_long"   , stBody.t5_can_use_long);
		pkt.GetParameterVal("t5_can_use_short"  , stBody.t5_can_use_short);
		pkt.GetParameterVal("t5_day_open_long"  , stBody.t5_day_open_long);
		pkt.GetParameterVal("t5_day_open_short" , stBody.t5_day_open_short);
		pkt.GetParameterVal("td_prod_code"      , stBody.td_prod_code);
		pkt.GetParameterVal("td_long_amt"       , stBody.td_long_amt);
		pkt.GetParameterVal("td_short_amt"      , stBody.td_short_amt);
		pkt.GetParameterVal("td_can_use_long"   , stBody.td_can_use_long);
		pkt.GetParameterVal("td_can_use_short"  , stBody.td_can_use_short);
		pkt.GetParameterVal("td_day_open_long"  , stBody.td_day_open_long);
		pkt.GetParameterVal("td_day_open_short" , stBody.td_day_open_short);
		pkt.GetParameterVal("td_day_cov_long"   , stBody.td_day_cov_long);
		pkt.GetParameterVal("td_day_cov_short"  , stBody.td_day_cov_short);
		pkt.GetParameterVal("td_day_deli_long"  , stBody.td_day_deli_long);
		pkt.GetParameterVal("td_day_deli_short" , stBody.td_day_deli_short);
		pkt.GetParameterVal("td_day_cov_long_froz", stBody.td_day_cov_long_froz);
		pkt.GetParameterVal("td_day_cov_short_froz", stBody.td_day_cov_short_froz);
		pkt.GetParameterVal("td_day_deli_long_forz", stBody.td_day_deli_long_forz);
		pkt.GetParameterVal("td_day_deli_short_forz", stBody.td_day_deli_short_forz);
		pkt.GetParameterVal("td_long_open_avg_price ", stBody.td_long_open_avg_price );
		pkt.GetParameterVal("td_short_open_avg_price", stBody.td_short_open_avg_price);
		pkt.GetParameterVal("td_long_posi_avg_price ", stBody.td_long_posi_avg_price );
		pkt.GetParameterVal("td_short_posi_avg_price", stBody.td_short_posi_avg_price);
		pkt.GetParameterVal("td_long_margin         ", stBody.td_long_margin         );
		pkt.GetParameterVal("td_short_margin        ", stBody.td_short_margin        );
		pkt.GetParameterVal("td_last_settle_price   ", stBody.td_last_settle_price   );
		pkt.GetParameterVal("td_day_settle_price    ", stBody.td_day_settle_price    );
		pkt.GetParameterVal("r_surplus"         , stBody.r_surplus);
		pkt.GetParameterVal("r_risk_index"      , stBody.r_risk_index);
		pkt.GetParameterVal("r_risk_level"      , stBody.r_risk_level);
		pkt.GetParameterVal("hlm_stor_info"     , stBody.hlm_stor_info);
		pkt.GetParameterVal("htm_t5_info"       , stBody.htm_t5_info);
		pkt.GetParameterVal("htm_td_info"       , stBody.htm_td_info);
		pkt.GetParameterVal("htm_prod_group_info"       , stBody.htm_prod_group_info);
		pkt.GetParameterVal("htm_acct_large_side_sum"       , stBody.htm_acct_large_side_sum);

		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �ͻ��ۺ���Ϣ��ѯ
	static int Struct2Packet(Rsp1020& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("c_acct_no"         , stBody.c_acct_no);
		pkt.AddParameter("c_cust_id"         , stBody.c_cust_id);
		pkt.AddParameter("c_account_no"      , stBody.c_account_no);
		pkt.AddParameter("c_open_bank_name"  , stBody.c_open_bank_name);
		pkt.AddParameter("c_cust_abbr"       , stBody.c_cust_abbr);
		pkt.AddParameter("c_b_fare_model_id" , stBody.c_b_fare_model_id);
		pkt.AddParameter("c_m_fare_model_id" , stBody.c_m_fare_model_id);
		pkt.AddParameter("c_acct_type"       , stBody.c_acct_type);
		pkt.AddParameter("c_ocma_flag"       , stBody.c_ocma_flag);
		pkt.AddParameter("c_acct_stat"       , stBody.c_acct_stat);
		pkt.AddParameter("c_broker_acct_no"  , stBody.c_broker_acct_no);
		pkt.AddParameter("c_cert_type"       , stBody.c_cert_type);
		pkt.AddParameter("c_cert_num"        , stBody.c_cert_num);
		pkt.AddParameter("c_branch_id"       , stBody.c_branch_id);
		pkt.AddParameter("c_trans_check_info", stBody.c_trans_check_info);
		pkt.AddParameter("f_currency_id"     , stBody.f_currency_id);
		pkt.AddParameter("f_curr_bal"        , stBody.f_curr_bal);
		pkt.AddParameter("f_can_use_bal"     , stBody.f_can_use_bal);
		pkt.AddParameter("f_can_get_bal"     , stBody.f_can_get_bal);
		pkt.AddParameter("f_in_bal"          , stBody.f_in_bal);
		pkt.AddParameter("f_out_bal"         , stBody.f_out_bal);
		pkt.AddParameter("f_buy_bal"         , stBody.f_buy_bal);
		pkt.AddParameter("f_sell_bal"        , stBody.f_sell_bal);
		pkt.AddParameter("f_exch_froz_bal"   , stBody.f_exch_froz_bal);
		pkt.AddParameter("f_posi_margin"     , stBody.f_posi_margin);
		pkt.AddParameter("f_base_margin"     , stBody.f_base_margin);
		pkt.AddParameter("f_take_margin"     , stBody.f_take_margin);
		pkt.AddParameter("f_stor_margin"     , stBody.f_stor_margin);
		pkt.AddParameter("f_pt_reserve"      , stBody.f_pt_reserve);
		pkt.AddParameter("f_ag_margin"       , stBody.f_ag_margin);
		pkt.AddParameter("f_forward_froz"    , stBody.f_forward_froz);
		pkt.AddParameter("f_exch_fare"       , stBody.f_exch_fare);
		pkt.AddParameter("s_variety_id"      , stBody.s_variety_id);
		pkt.AddParameter("s_curr_amt"        , stBody.s_curr_amt);
		pkt.AddParameter("s_can_use_amt"     , stBody.s_can_use_amt);
		pkt.AddParameter("s_can_get_amt"     , stBody.s_can_get_amt);
		pkt.AddParameter("s_day_deposit"     , stBody.s_day_deposit);
		pkt.AddParameter("s_day_draw"        , stBody.s_day_draw);
		pkt.AddParameter("s_real_buy_amt"    , stBody.s_real_buy_amt);
		pkt.AddParameter("s_real_sell_amt"   , stBody.s_real_sell_amt);
		pkt.AddParameter("s_entr_sell_amt"   , stBody.s_entr_sell_amt);
		pkt.AddParameter("s_app_froz_amt"    , stBody.s_app_froz_amt);
		pkt.AddParameter("s_unit_cost"       , stBody.s_unit_cost);
		pkt.AddParameter("t5_prod_code"      , stBody.t5_prod_code);
		pkt.AddParameter("t5_long_amt"       , stBody.t5_long_amt);
		pkt.AddParameter("t5_short_amt"      , stBody.t5_short_amt);
		pkt.AddParameter("t5_can_use_long"   , stBody.t5_can_use_long);
		pkt.AddParameter("t5_can_use_short"  , stBody.t5_can_use_short);
		pkt.AddParameter("t5_day_open_long"  , stBody.t5_day_open_long);
		pkt.AddParameter("t5_day_open_short" , stBody.t5_day_open_short);
		pkt.AddParameter("td_prod_code"      , stBody.td_prod_code);
		pkt.AddParameter("td_long_amt"       , stBody.td_long_amt);
		pkt.AddParameter("td_short_amt"      , stBody.td_short_amt);
		pkt.AddParameter("td_can_use_long"   , stBody.td_can_use_long);
		pkt.AddParameter("td_can_use_short"  , stBody.td_can_use_short);
		pkt.AddParameter("td_day_open_long"  , stBody.td_day_open_long);
		pkt.AddParameter("td_day_open_short" , stBody.td_day_open_short);
		pkt.AddParameter("td_day_cov_long"   , stBody.td_day_cov_long);
		pkt.AddParameter("td_day_cov_short"  , stBody.td_day_cov_short);
		pkt.AddParameter("td_day_deli_long"  , stBody.td_day_deli_long);
		pkt.AddParameter("td_day_deli_short" , stBody.td_day_deli_short);
		pkt.AddParameter("td_day_cov_long_froz", stBody.td_day_cov_long_froz);
		pkt.AddParameter("td_day_cov_short_froz", stBody.td_day_cov_short_froz);
		pkt.AddParameter("td_day_deli_long_forz", stBody.td_day_deli_long_forz);
		pkt.AddParameter("td_day_deli_short_forz", stBody.td_day_deli_short_forz);
		pkt.AddParameter("td_long_open_avg_price ", stBody.td_long_open_avg_price );
		pkt.AddParameter("td_short_open_avg_price", stBody.td_short_open_avg_price);
		pkt.AddParameter("td_long_posi_avg_price ", stBody.td_long_posi_avg_price );
		pkt.AddParameter("td_short_posi_avg_price", stBody.td_short_posi_avg_price);
		pkt.AddParameter("td_long_margin         ", stBody.td_long_margin         );
		pkt.AddParameter("td_short_margin        ", stBody.td_short_margin        );
		pkt.AddParameter("td_last_settle_price   ", stBody.td_last_settle_price   );
		pkt.AddParameter("td_day_settle_price    ", stBody.td_day_settle_price    );
		pkt.AddParameter("r_surplus"         , stBody.r_surplus);
		pkt.AddParameter("r_risk_index"      , stBody.r_risk_index);
		pkt.AddParameter("r_risk_level"      , stBody.r_risk_level);
		pkt.AddParameter("hlm_stor_info"     , stBody.hlm_stor_info);
		pkt.AddParameter("htm_t5_info"       , stBody.htm_t5_info);
		pkt.AddParameter("htm_td_info"       , stBody.htm_td_info);
		pkt.AddParameter("htm_prod_group_info"       , stBody.htm_prod_group_info);
		pkt.AddParameter("htm_acct_large_side_sum"       , stBody.htm_acct_large_side_sum);

		return 0;
	};



	// ���Ľ��������� -> �ṹ    �˻������޸ĵ���������
	static int Packet2Struct(Req2022& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("acct_type"         , stBody.acct_type);
		pkt.GetParameterVal("old_exch_pwd"      , stBody.old_exch_pwd);
		pkt.GetParameterVal("exch_pwd"          , stBody.exch_pwd);
		pkt.GetParameterVal("old_fund_pwd"      , stBody.old_fund_pwd);
		pkt.GetParameterVal("fund_pwd"          , stBody.fund_pwd);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �˻������޸ĵ���������
	static int Struct2Packet(Req2022& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("acct_type"         , stBody.acct_type);
		pkt.AddParameter("old_exch_pwd"      , stBody.old_exch_pwd);
		pkt.AddParameter("exch_pwd"          , stBody.exch_pwd);
		pkt.AddParameter("old_fund_pwd"      , stBody.old_fund_pwd);
		pkt.AddParameter("fund_pwd"          , stBody.fund_pwd);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    �˻������޸ĵ���Ӧ������
	static int Packet2Struct(Rsp2022& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �˻������޸ĵ���Ӧ������
	static int Struct2Packet(Rsp2022& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    �ͻ�ʵ�ʷ��ʲ�ѯ����������
	static int Packet2Struct(Req2040& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �ͻ�ʵ�ʷ��ʲ�ѯ����������
	static int Struct2Packet(Req2040& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    �ͻ�ʵ�ʷ��ʲ�ѯ����Ӧ������
	static int Packet2Struct(Rsp2040& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("alm_b_fare_list"   , stBody.alm_b_fare_list);
		pkt.GetParameterVal("alm_m_fare_list"   , stBody.alm_m_fare_list);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �ͻ�ʵ�ʷ��ʲ�ѯ����Ӧ������
	static int Struct2Packet(Rsp2040& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("alm_b_fare_list"   , stBody.alm_b_fare_list);
		pkt.AddParameter("alm_m_fare_list"   , stBody.alm_m_fare_list);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    �սᵥȷ�ϵ���������
	static int Packet2Struct(Req2201& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("affirm_date"       , stBody.affirm_date);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �սᵥȷ�ϵ���������
	static int Struct2Packet(Req2201& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("affirm_date"       , stBody.affirm_date);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    �սᵥȷ�ϵ���Ӧ������
	static int Packet2Struct(Rsp2201& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("affirm_date"       , stBody.affirm_date);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �սᵥȷ�ϵ���Ӧ������
	static int Struct2Packet(Rsp2201& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("affirm_date"       , stBody.affirm_date);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    �Զ������ת�˵���������
	static int Struct2Packet(Req3010& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("serial_no"         , stBody.serial_no);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("access_way"        , stBody.access_way);
		pkt.AddParameter("exch_bal"          , stBody.exch_bal);
		pkt.AddParameter("remark"            , stBody.remark);
		pkt.AddParameter("cust_id"           , stBody.cust_id);
		pkt.AddParameter("cust_abbr"         , stBody.cust_abbr);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("c_status"          , stBody.c_status);
		pkt.AddParameter("o_teller_id"       , stBody.o_teller_id);
		pkt.AddParameter("account_no"        , stBody.account_no);
		pkt.AddParameter("open_bank_name"    , stBody.open_bank_name);
		pkt.AddParameter("fund_pwd"          , stBody.fund_pwd);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    �Զ������ת�˵���Ӧ������
	static int Packet2Struct(Rsp3010& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("serial_no"         , stBody.serial_no);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("cust_id"           , stBody.cust_id);
		pkt.GetParameterVal("cust_abbr"         , stBody.cust_abbr);
		pkt.GetParameterVal("acct_stat"         , stBody.acct_stat);
		pkt.GetParameterVal("exec_name"         , stBody.exec_name);
		pkt.GetParameterVal("exec_cert_num"     , stBody.exec_cert_num);
		pkt.GetParameterVal("curr_bal"          , stBody.curr_bal);
		pkt.GetParameterVal("can_get_cash"      , stBody.can_get_cash);
		pkt.GetParameterVal("can_use_cash"      , stBody.can_use_cash);
		pkt.GetParameterVal("alm_custtype_list" , stBody.alm_custtype_list);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    �Զ������ת�˵���������
	static int Packet2Struct(Req3021& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("access_way"        , stBody.access_way);
		pkt.GetParameterVal("exch_bal"          , stBody.exch_bal);
		pkt.GetParameterVal("fund_pwd"          , stBody.fund_pwd);
		pkt.GetParameterVal("remark"            , stBody.remark);
		pkt.GetParameterVal("cust_id"           , stBody.cust_id);
		pkt.GetParameterVal("cust_abbr"         , stBody.cust_abbr);
		pkt.GetParameterVal("cust_type"         , stBody.cust_type);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("card_pwd"         , stBody.card_pwd);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �Զ������ת�˵���������
	static int Struct2Packet(Req3021& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("access_way"        , stBody.access_way);
		pkt.AddParameter("exch_bal"          , stBody.exch_bal);
		pkt.AddParameter("fund_pwd"          , stBody.fund_pwd);
		pkt.AddParameter("remark"            , stBody.remark);
		pkt.AddParameter("cust_id"           , stBody.cust_id);
		pkt.AddParameter("cust_abbr"         , stBody.cust_abbr);
		pkt.AddParameter("cust_type"         , stBody.cust_type);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("card_pwd"         , stBody.card_pwd);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    �Զ������ת�˵���Ӧ������
	static int Packet2Struct(Rsp3021& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("alm_custtype_list" , stBody.alm_custtype_list);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �Զ������ת�˵���Ӧ������
	static int Struct2Packet(Rsp3021& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("alm_custtype_list" , stBody.alm_custtype_list);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �Զ������ת�˵���������
	static int Struct2Packet(Rep3024& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"       , stBody.oper_flag);
		pkt.AddParameter("acct_no"         , stBody.acct_no);
		pkt.AddParameter("bank_no"         , stBody.bank_no);
		pkt.AddParameter("bk_mer_code"     , stBody.bk_mer_code);
		pkt.AddParameter("bk_cust_no"      , stBody.bk_cust_no);
		pkt.AddParameter("bk_acct_name"    , stBody.bk_acct_name);
		pkt.AddParameter("bk_acct_no"      , stBody.bk_acct_no);
		pkt.AddParameter("bk_cert_type"    , stBody.bk_cert_type);
		pkt.AddParameter("bk_cert_no"      , stBody.bk_cert_no);
		pkt.AddParameter("sms_flag"        , stBody.sms_flag);
		pkt.AddParameter("phone_num"       , stBody.phone_num);
		pkt.AddParameter("remark"          , stBody.remark);

		return 0;
	};

	// ���Ľ��������� -> �ṹ    �Զ������ת�˵���Ӧ������
	static int Packet2Struct(Rsp3024& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"       , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"         , stBody.acct_no);
		pkt.GetParameterVal("bank_no"         , stBody.bank_no);
		pkt.GetParameterVal("bk_mer_code"     , stBody.bk_mer_code);
		pkt.GetParameterVal("bk_cust_no"      , stBody.bk_cust_no);
		pkt.GetParameterVal("bk_acct_name"    , stBody.bk_acct_name);
		pkt.GetParameterVal("bk_acct_no"      , stBody.bk_acct_no);
		pkt.GetParameterVal("bk_cert_type"    , stBody.bk_cert_type);
		pkt.GetParameterVal("bk_cert_no"      , stBody.bk_cert_no);
		pkt.GetParameterVal("sms_flag"        , stBody.sms_flag);
		pkt.GetParameterVal("phone_num"       , stBody.phone_num);
		pkt.GetParameterVal("remark"          , stBody.remark);

		return 0;
	};


	// ���Ľ��������� -> �ṹ    ����ȡ����������
	static int Packet2Struct(Req3064& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("begin_time"        , stBody.begin_time);
		pkt.GetParameterVal("end_time"          , stBody.end_time);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("tip_type"          , stBody.tip_type);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����������
	static int Struct2Packet(Req3064& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("begin_time"         , stBody.begin_time);
		pkt.AddParameter("end_time"         , stBody.end_time);
		pkt.AddParameter("acct_no"         , stBody.acct_no);
		pkt.AddParameter("tip_type"         , stBody.tip_type);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp3064& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("alm_result"       , stBody.alm_result);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����Ӧ������
	static int Struct2Packet(Rsp3064& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("alm_result"       , stBody.alm_result);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ����ȡ����������
	static int Packet2Struct(Req3069& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"                , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"                  , stBody.acct_no);
		pkt.GetParameterVal("instid"                   , stBody.instid);
		pkt.GetParameterVal("gene_type"                , stBody.gene_type);
		pkt.GetParameterVal("begin_date"               , stBody.begin_date);
		pkt.GetParameterVal("end_date"                 , stBody.end_date);
		pkt.GetParameterVal("order_status_set"         , stBody.order_status_set);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����������
	static int Struct2Packet(Req3069& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"                , stBody.oper_flag);
		pkt.AddParameter("acct_no"                  , stBody.acct_no);
		pkt.AddParameter("instid"                   , stBody.instid);
		pkt.AddParameter("gene_type"                , stBody.gene_type);
		pkt.AddParameter("begin_date"               , stBody.begin_date);
		pkt.AddParameter("end_date"                 , stBody.end_date);
		pkt.AddParameter("order_status_set"         , stBody.order_status_set);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp3069& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"                , stBody.oper_flag);
		pkt.GetParameterVal("alm_result"         , stBody.order_status_set);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����Ӧ������
	static int Struct2Packet(Rsp3069& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"                , stBody.oper_flag);
		pkt.AddParameter("order_status_set"         , stBody.order_status_set);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ����ȡ����������
	static int Packet2Struct(Req3099& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����������
	static int Struct2Packet(Req3099& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp3099& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("risk_degree1"       , stBody.risk_degree1);
		pkt.GetParameterVal("risk_degree2"       , stBody.risk_degree2);
		pkt.GetParameterVal("risk_grade"        , stBody.risk_grade);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����Ӧ������
	static int Struct2Packet(Rsp3099& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("risk_degree1"       , stBody.risk_degree1);
		pkt.AddParameter("risk_degree2"       , stBody.risk_degree2);
		pkt.AddParameter("risk_grade"        , stBody.risk_grade);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ��֤�𻮲�����������
	static int Packet2Struct(Req3101& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("serial_no"         , stBody.serial_no);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("access_way"        , stBody.access_way);
		pkt.GetParameterVal("exch_bal"          , stBody.exch_bal);
		pkt.GetParameterVal("remark"            , stBody.remark);
		pkt.GetParameterVal("fund_pwd"          , stBody.fund_pwd);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("grade_id"          , stBody.grade_id);
		pkt.GetParameterVal("o_term_type"       , stBody.o_term_type);
		pkt.GetParameterVal("send_stat"         , stBody.send_stat);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ��֤�𻮲�����������
	static int Struct2Packet(Req3101& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("serial_no"         , stBody.serial_no);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("access_way"        , stBody.access_way);
		pkt.AddParameter("exch_bal"          , stBody.exch_bal);
		pkt.AddParameter("remark"            , stBody.remark);
		pkt.AddParameter("fund_pwd"          , stBody.fund_pwd);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("grade_id"          , stBody.grade_id);
		pkt.AddParameter("o_term_type"       , stBody.o_term_type);
		pkt.AddParameter("send_stat"         , stBody.send_stat);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ��֤�𻮲�����Ӧ������
	static int Packet2Struct(Rsp3101& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("Exch_date"         , stBody.Exch_date);
		pkt.GetParameterVal("Serial_no"         , stBody.Serial_no);
		pkt.GetParameterVal("Acct_no"           , stBody.Acct_no);
		pkt.GetParameterVal("bank_no"           , stBody.bank_no);
		pkt.GetParameterVal("f_busi_type"       , stBody.f_busi_type);
		pkt.GetParameterVal("access_way"        , stBody.access_way);
		pkt.GetParameterVal("out_account_no"    , stBody.out_account_no);
		pkt.GetParameterVal("in_account_no"     , stBody.in_account_no);
		pkt.GetParameterVal("Exch_bal"          , stBody.Exch_bal);
		pkt.GetParameterVal("check_stat1"       , stBody.check_stat1);
		pkt.GetParameterVal("check_stat2"       , stBody.check_stat2);
		pkt.GetParameterVal("send_stat"         , stBody.send_stat);
		pkt.GetParameterVal("in_account_flag"   , stBody.in_account_flag);
		pkt.GetParameterVal("remark"            , stBody.remark);
		pkt.GetParameterVal("bk_plat_date"      , stBody.bk_plat_date);
		pkt.GetParameterVal("bk_seq_no"         , stBody.bk_seq_no);
		pkt.GetParameterVal("bk_rsp_code"       , stBody.bk_rsp_code);
		pkt.GetParameterVal("bk_rsp_msg"        , stBody.bk_rsp_msg);
		pkt.GetParameterVal("o_term_type"       , stBody.o_term_type);
		pkt.GetParameterVal("o_teller_id"       , stBody.o_teller_id);
		pkt.GetParameterVal("o_date"            , stBody.o_date);
		pkt.GetParameterVal("c_term_type1"      , stBody.c_term_type1);
		pkt.GetParameterVal("c_teller_id1"      , stBody.c_teller_id1);
		pkt.GetParameterVal("c_date1"           , stBody.c_date1);
		pkt.GetParameterVal("c_term_type2"      , stBody.c_term_type2);
		pkt.GetParameterVal("c_teller_id2"      , stBody.c_teller_id2);
		pkt.GetParameterVal("c_date2"           , stBody.c_date2);
		pkt.GetParameterVal("htm_result"        , stBody.htm_result);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ��֤�𻮲�����Ӧ������
	static int Struct2Packet(Rsp3101& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("Exch_date"         , stBody.Exch_date);
		pkt.AddParameter("Serial_no"         , stBody.Serial_no);
		pkt.AddParameter("Acct_no"           , stBody.Acct_no);
		pkt.AddParameter("bank_no"           , stBody.bank_no);
		pkt.AddParameter("f_busi_type"       , stBody.f_busi_type);
		pkt.AddParameter("access_way"        , stBody.access_way);
		pkt.AddParameter("out_account_no"    , stBody.out_account_no);
		pkt.AddParameter("in_account_no"     , stBody.in_account_no);
		pkt.AddParameter("Exch_bal"          , stBody.Exch_bal);
		pkt.AddParameter("check_stat1"       , stBody.check_stat1);
		pkt.AddParameter("check_stat2"       , stBody.check_stat2);
		pkt.AddParameter("send_stat"         , stBody.send_stat);
		pkt.AddParameter("in_account_flag"   , stBody.in_account_flag);
		pkt.AddParameter("remark"            , stBody.remark);
		pkt.AddParameter("bk_plat_date"      , stBody.bk_plat_date);
		pkt.AddParameter("bk_seq_no"         , stBody.bk_seq_no);
		pkt.AddParameter("bk_rsp_code"       , stBody.bk_rsp_code);
		pkt.AddParameter("bk_rsp_msg"        , stBody.bk_rsp_msg);
		pkt.AddParameter("o_term_type"       , stBody.o_term_type);
		pkt.AddParameter("o_teller_id"       , stBody.o_teller_id);
		pkt.AddParameter("o_date"            , stBody.o_date);
		pkt.AddParameter("c_term_type1"      , stBody.c_term_type1);
		pkt.AddParameter("c_teller_id1"      , stBody.c_teller_id1);
		pkt.AddParameter("c_date1"           , stBody.c_date1);
		pkt.AddParameter("c_term_type2"      , stBody.c_term_type2);
		pkt.AddParameter("c_teller_id2"      , stBody.c_teller_id2);
		pkt.AddParameter("c_date2"           , stBody.c_date2);
		pkt.AddParameter("htm_result"        , stBody.htm_result);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ȡ����Ӧ������
	static int Struct2Packet(Req3201& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"       , stBody.oper_flag);
		pkt.AddParameter("acct_no"         , stBody.acct_no);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp3201& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"      , stBody.oper_flag);
		pkt.GetParameterVal("card_bal"       , stBody.card_bal);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ����ͳһ������
	static int Packet2Struct(Req4001& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);//add by xiao
		pkt.GetParameterVal("client_serial_no"  , stBody.client_serial_no);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("cust_id"           , stBody.cust_id);
		pkt.GetParameterVal("bank_no"           , stBody.bank_no);
		pkt.GetParameterVal("b_market_id"       , stBody.b_market_id);
		pkt.GetParameterVal("prod_code"         , stBody.prod_code);
		pkt.GetParameterVal("offset_flag"       , stBody.offset_flag);
		pkt.GetParameterVal("deli_flag"         , stBody.deli_flag);
		pkt.GetParameterVal("bs"                , stBody.bs);
		pkt.GetParameterVal("entr_price"        , stBody.entr_price);
		pkt.GetParameterVal("entr_amount"       , stBody.entr_amount);
		pkt.GetParameterVal("cov_type"          , stBody.cov_type);
		pkt.GetParameterVal("match_type"        , stBody.match_type);
		pkt.GetParameterVal("src_match_no"      , stBody.src_match_no);
		pkt.GetParameterVal("order_send_type"   , stBody.order_send_type);
		pkt.GetParameterVal("auto_send_time_s"  , stBody.auto_send_time_s);
		pkt.GetParameterVal("auto_send_time_e"  , stBody.auto_send_time_e);
		pkt.GetParameterVal("auto_send_stat_s"  , stBody.auto_send_stat_s);
		pkt.GetParameterVal("auto_send_stat_t"  , stBody.auto_send_stat_t);
		pkt.GetParameterVal("auto_send_way"     , stBody.auto_send_way);
		pkt.GetParameterVal("auto_send_comp"    , stBody.auto_send_comp);
		pkt.GetParameterVal("auto_send_price"   , stBody.auto_send_price);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ͳһ������
	static int Struct2Packet(Req4001& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);//add by xiao
		pkt.AddParameter("client_serial_no"  , stBody.client_serial_no);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("cust_id"           , stBody.cust_id);
		pkt.AddParameter("bank_no"           , stBody.bank_no);
		pkt.AddParameter("b_market_id"       , stBody.b_market_id);
		pkt.AddParameter("prod_code"         , stBody.prod_code);
		pkt.AddParameter("offset_flag"       , stBody.offset_flag);
		pkt.AddParameter("deli_flag"         , stBody.deli_flag);
		pkt.AddParameter("bs"                , stBody.bs);
		pkt.AddParameter("entr_price"        , stBody.entr_price);
		pkt.AddParameter("entr_amount"       , stBody.entr_amount);
		pkt.AddParameter("cov_type"          , stBody.cov_type);
		pkt.AddParameter("match_type"        , stBody.match_type);
		pkt.AddParameter("src_match_no"      , stBody.src_match_no);
		pkt.AddParameter("order_send_type"   , stBody.order_send_type);
		pkt.AddParameter("auto_send_time_s"  , stBody.auto_send_time_s);
		pkt.AddParameter("auto_send_time_e"  , stBody.auto_send_time_e);
		pkt.AddParameter("auto_send_stat_s"  , stBody.auto_send_stat_s);
		pkt.AddParameter("auto_send_stat_t"  , stBody.auto_send_stat_t);
		pkt.AddParameter("auto_send_way"     , stBody.auto_send_way);
		pkt.AddParameter("auto_send_comp"    , stBody.auto_send_comp);
		pkt.AddParameter("auto_send_price"   , stBody.auto_send_price);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ����ͳһ������
	static int Packet2Struct(Rsp4001& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("client_serial_no"  , stBody.client_serial_no);
		pkt.GetParameterVal("local_order_no"    , stBody.local_order_no);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����ͳһ������
	static int Struct2Packet(Rsp4001& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("client_serial_no"  , stBody.client_serial_no);
		pkt.AddParameter("local_order_no"    , stBody.local_order_no);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ���׳���
	static int Packet2Struct(Req4061& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("cancel_order_no"   , stBody.cancel_order_no);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ���׳���
	static int Struct2Packet(Req4061& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("cancel_order_no"   , stBody.cancel_order_no);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ���׳���
	static int Packet2Struct(Rsp4061& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ���׳���
	static int Struct2Packet(Rsp4061& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ƽ�������������
	static int Packet2Struct(Req4071& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("prod_code"         , stBody.prod_code);
		pkt.GetParameterVal("cov_bs"            , stBody.cov_bs);
		pkt.GetParameterVal("cov_price"         , stBody.cov_price);
		pkt.GetParameterVal("cov_amount"        , stBody.cov_amount);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ƽ�������������
	static int Struct2Packet(Req4071& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("prod_code"         , stBody.prod_code);
		pkt.AddParameter("cov_bs"            , stBody.cov_bs);
		pkt.AddParameter("cov_price"         , stBody.cov_price);
		pkt.AddParameter("cov_amount"        , stBody.cov_amount);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ƽ���������Ӧ����
	static int Packet2Struct(Rsp4071& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("cust_abbr"         , stBody.cust_abbr);
		pkt.GetParameterVal("prod_code"         , stBody.prod_code);
		pkt.GetParameterVal("remain_long"       , stBody.remain_long);
		pkt.GetParameterVal("remain_short"      , stBody.remain_short);
		pkt.GetParameterVal("cov_exch_fare"     , stBody.cov_exch_fare);
		pkt.GetParameterVal("cov_surplus"       , stBody.cov_surplus);
		pkt.GetParameterVal("can_use_bal"       , stBody.can_use_bal);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ƽ���������Ӧ����
	static int Struct2Packet(Rsp4071& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("cust_abbr"         , stBody.cust_abbr);
		pkt.AddParameter("prod_code"         , stBody.prod_code);
		pkt.AddParameter("remain_long"       , stBody.remain_long);
		pkt.AddParameter("remain_short"      , stBody.remain_short);
		pkt.AddParameter("cov_exch_fare"     , stBody.cov_exch_fare);
		pkt.AddParameter("cov_surplus"       , stBody.cov_surplus);
		pkt.AddParameter("can_use_bal"       , stBody.can_use_bal);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ���������ά������������
	static int Packet2Struct(Req5041& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("year"              , stBody.year);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("is_search_usefull" , stBody.is_search_usefull);
		pkt.GetParameterVal("search_num"        , stBody.search_num);
		pkt.GetParameterVal("alm_take_sheet_date", stBody.alm_take_sheet_date);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ���������ά������������
	static int Struct2Packet(Req5041& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("year"              , stBody.year);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("is_search_usefull" , stBody.is_search_usefull);
		pkt.AddParameter("search_num"        , stBody.search_num);
		pkt.AddParameter("alm_take_sheet_date", stBody.alm_take_sheet_date);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ���������ά������Ӧ������
	static int Packet2Struct(Rsp5041& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("year"              , stBody.year);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("alm_take_sheet_date", stBody.alm_take_sheet_date);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ���������ά������Ӧ������
	static int Struct2Packet(Rsp5041& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("year"              , stBody.year);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("alm_take_sheet_date", stBody.alm_take_sheet_date);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ���ӿڵ����������ˮά������������
	static int Packet2Struct(Req5101& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("local_sheet_no"    , stBody.local_sheet_no);
		pkt.GetParameterVal("sheet_no"          , stBody.sheet_no);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("cust_id"           , stBody.cust_id);
		pkt.GetParameterVal("variety_id"        , stBody.variety_id);
		pkt.GetParameterVal("app_amount"        , stBody.app_amount);
		pkt.GetParameterVal("city_code"         , stBody.city_code);
		pkt.GetParameterVal("stor_id"           , stBody.stor_id);
		pkt.GetParameterVal("take_man"          , stBody.take_man);
		pkt.GetParameterVal("cert_type_id"      , stBody.cert_type_id);
		pkt.GetParameterVal("cert_num"          , stBody.cert_num);
		pkt.GetParameterVal("app_pwd"           , stBody.app_pwd);
		pkt.GetParameterVal("app_record"        , stBody.app_record);
		pkt.GetParameterVal("take_date"         , stBody.take_date);
		pkt.GetParameterVal("start_date"        , stBody.start_date);
		pkt.GetParameterVal("end_date"          , stBody.end_date);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ���ӿڵ����������ˮά������������
	static int Struct2Packet(Req5101& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("local_sheet_no"    , stBody.local_sheet_no);
		pkt.AddParameter("sheet_no"          , stBody.sheet_no);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("cust_id"           , stBody.cust_id);
		pkt.AddParameter("variety_id"        , stBody.variety_id);
		pkt.AddParameter("app_amount"        , stBody.app_amount);
		pkt.AddParameter("city_code"         , stBody.city_code);
		pkt.AddParameter("stor_id"           , stBody.stor_id);
		pkt.AddParameter("take_man"          , stBody.take_man);
		pkt.AddParameter("cert_type_id"      , stBody.cert_type_id);
		pkt.AddParameter("cert_num"          , stBody.cert_num);
		pkt.AddParameter("app_pwd"           , stBody.app_pwd);
		pkt.AddParameter("app_record"        , stBody.app_record);
		pkt.AddParameter("take_date"         , stBody.take_date);
		pkt.AddParameter("start_date"        , stBody.start_date);
		pkt.AddParameter("end_date"          , stBody.end_date);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ���������ˮ��ѯ����Ӧ������
	static int Packet2Struct(Rsp5101& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("local_sheet_no"    , stBody.local_sheet_no);
		pkt.GetParameterVal("sheet_no"          , stBody.sheet_no);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("cust_id"           , stBody.cust_id);
		pkt.GetParameterVal("variety_id"        , stBody.variety_id);
		pkt.GetParameterVal("app_amount"        , stBody.app_amount);
		pkt.GetParameterVal("draw_type"         , stBody.draw_type);
		pkt.GetParameterVal("self_draw"         , stBody.self_draw);
		pkt.GetParameterVal("trade_draw"        , stBody.trade_draw);
		pkt.GetParameterVal("city_code"         , stBody.city_code);
		pkt.GetParameterVal("stor_id"           , stBody.stor_id);
		pkt.GetParameterVal("take_man"          , stBody.take_man);
		pkt.GetParameterVal("cert_type_id"      , stBody.cert_type_id);
		pkt.GetParameterVal("cert_num"          , stBody.cert_num);
		pkt.GetParameterVal("app_record"        , stBody.app_record);
		pkt.GetParameterVal("app_date"          , stBody.app_date);
		pkt.GetParameterVal("app_time"          , stBody.app_time);
		pkt.GetParameterVal("app_exch_date"     , stBody.app_exch_date);
		pkt.GetParameterVal("app_start_date"    , stBody.app_start_date);
		pkt.GetParameterVal("app_end_date"      , stBody.app_end_date);
		pkt.GetParameterVal("due_take_date"     , stBody.due_take_date);
		pkt.GetParameterVal("stat"              , stBody.stat);
		pkt.GetParameterVal("cancel_date"       , stBody.cancel_date);
		pkt.GetParameterVal("cancel_time"       , stBody.cancel_time);
		pkt.GetParameterVal("cancel_exch_date"  , stBody.cancel_exch_date);
		pkt.GetParameterVal("cancel_record"     , stBody.cancel_record);
		pkt.GetParameterVal("send_stat"         , stBody.send_stat);
		pkt.GetParameterVal("take_margin"       , stBody.take_margin);
		pkt.GetParameterVal("is_other_take"     , stBody.is_other_take);
		pkt.GetParameterVal("take_affirm"       , stBody.take_affirm);
		pkt.GetParameterVal("htm_take_sheet_detail", stBody.htm_take_sheet_detail);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ���������ˮ��ѯ����Ӧ������
	static int Struct2Packet(Rsp5101& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("local_sheet_no"    , stBody.local_sheet_no);
		pkt.AddParameter("sheet_no"          , stBody.sheet_no);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("cust_id"           , stBody.cust_id);
		pkt.AddParameter("variety_id"        , stBody.variety_id);
		pkt.AddParameter("app_amount"        , stBody.app_amount);
		pkt.AddParameter("draw_type"         , stBody.draw_type);
		pkt.AddParameter("self_draw"         , stBody.self_draw);
		pkt.AddParameter("trade_draw"        , stBody.trade_draw);
		pkt.AddParameter("city_code"         , stBody.city_code);
		pkt.AddParameter("stor_id"           , stBody.stor_id);
		pkt.AddParameter("take_man"          , stBody.take_man);
		pkt.AddParameter("cert_type_id"      , stBody.cert_type_id);
		pkt.AddParameter("cert_num"          , stBody.cert_num);
		pkt.AddParameter("app_record"        , stBody.app_record);
		pkt.AddParameter("app_date"          , stBody.app_date);
		pkt.AddParameter("app_time"          , stBody.app_time);
		pkt.AddParameter("app_exch_date"     , stBody.app_exch_date);
		pkt.AddParameter("app_start_date"    , stBody.app_start_date);
		pkt.AddParameter("app_end_date"      , stBody.app_end_date);
		pkt.AddParameter("due_take_date"     , stBody.due_take_date);
		pkt.AddParameter("stat"              , stBody.stat);
		pkt.AddParameter("cancel_date"       , stBody.cancel_date);
		pkt.AddParameter("cancel_time"       , stBody.cancel_time);
		pkt.AddParameter("cancel_exch_date"  , stBody.cancel_exch_date);
		pkt.AddParameter("cancel_record"     , stBody.cancel_record);
		pkt.AddParameter("send_stat"         , stBody.send_stat);
		pkt.AddParameter("take_margin"       , stBody.take_margin);
		pkt.AddParameter("is_other_take"     , stBody.is_other_take);
		pkt.AddParameter("take_affirm"       , stBody.take_affirm);
		pkt.AddParameter("htm_take_sheet_detail", stBody.htm_take_sheet_detail);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    �������ӡ������
	static int Packet2Struct(Req5103& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("local_sheet_no"    , stBody.local_sheet_no);
		pkt.GetParameterVal("sheet_no"          , stBody.sheet_no);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("cust_id      "     , stBody.cust_id      );
		pkt.GetParameterVal("start_date"        , stBody.start_date);
		pkt.GetParameterVal("end_date"          , stBody.end_date);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �������ӡ������
	static int Struct2Packet(Req5103& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("local_sheet_no"    , stBody.local_sheet_no);
		pkt.AddParameter("sheet_no"          , stBody.sheet_no);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("cust_id      "     , stBody.cust_id      );
		pkt.AddParameter("start_date"        , stBody.start_date);
		pkt.AddParameter("end_date"          , stBody.end_date);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    �������ӡ��Ӧ����
	static int Packet2Struct(Rsp5103& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("alm_take_sheet_detail", stBody.alm_take_sheet_detail);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �������ӡ��Ӧ����
	static int Struct2Packet(Rsp5103& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("alm_take_sheet_detail", stBody.alm_take_sheet_detail);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ��ѯ�������ò�ѯ
	static int Packet2Struct(Req6001& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("query_id"          , stBody.query_id);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ��ѯ�������ò�ѯ
	static int Struct2Packet(Req6001& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("query_id"          , stBody.query_id);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ��ѯ�������ò�ѯ����Ӧ������
	static int Packet2Struct(Rsp6001& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("query_id"          , stBody.query_id);
		pkt.GetParameterVal("query_name"        , stBody.query_name);
		pkt.GetParameterVal("cell_num"          , stBody.cell_num);
		pkt.GetParameterVal("cell_inv_width"    , stBody.cell_inv_width);
		pkt.GetParameterVal("cell_inv_height"   , stBody.cell_inv_height);
		pkt.GetParameterVal("alm_options"       , stBody.alm_options);
		pkt.GetParameterVal("alm_field_en_name" , stBody.alm_field_en_name);
		pkt.GetParameterVal("alm_field_cn_name" , stBody.alm_field_cn_name);
		pkt.GetParameterVal("alm_field_width"   , stBody.alm_field_width);
		pkt.GetParameterVal("alm_field_align"   , stBody.alm_field_align);
		pkt.GetParameterVal("alm_field_format"  , stBody.alm_field_format);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ��ѯ�������ò�ѯ����Ӧ������
	static int Struct2Packet(Rsp6001& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("query_id"          , stBody.query_id);
		pkt.AddParameter("query_name"        , stBody.query_name);
		pkt.AddParameter("cell_num"          , stBody.cell_num);
		pkt.AddParameter("cell_inv_width"    , stBody.cell_inv_width);
		pkt.AddParameter("cell_inv_height"   , stBody.cell_inv_height);
		pkt.AddParameter("alm_options"       , stBody.alm_options);
		pkt.AddParameter("alm_field_en_name" , stBody.alm_field_en_name);
		pkt.AddParameter("alm_field_cn_name" , stBody.alm_field_cn_name);
		pkt.AddParameter("alm_field_width"   , stBody.alm_field_width);
		pkt.AddParameter("alm_field_align"   , stBody.alm_field_align);
		pkt.AddParameter("alm_field_format"  , stBody.alm_field_format);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ��ͨ��ѯ
	static int Packet2Struct(Req6002& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("login_branch_id"   , stBody.login_branch_id);
		pkt.GetParameterVal("login_teller_id"   , stBody.login_teller_id);
		pkt.GetParameterVal("paginal_num"       , stBody.paginal_num);
		pkt.GetParameterVal("curr_page"         , stBody.curr_page);
		pkt.GetParameterVal("query_id"          , stBody.query_id);
		pkt.GetParameterVal("alm_view_field"    , stBody.alm_view_field);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ��ͨ��ѯ
	static int Struct2Packet(Req6002& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("login_branch_id"   , stBody.login_branch_id);
		pkt.AddParameter("login_teller_id"   , stBody.login_teller_id);
		pkt.AddParameter("paginal_num"       , stBody.paginal_num);
		pkt.AddParameter("curr_page"         , stBody.curr_page);
		pkt.AddParameter("query_id"          , stBody.query_id);
		pkt.AddParameter("alm_view_field"    , stBody.alm_view_field);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ��ͨ��ѯ
	static int Packet2Struct(Rsp6002& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("paginal_num"       , stBody.paginal_num);
		pkt.GetParameterVal("page_count"        , stBody.page_count);
		pkt.GetParameterVal("curr_page"         , stBody.curr_page);
		pkt.GetParameterVal("alm_result"        , stBody.alm_result);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ��ͨ��ѯ
	static int Struct2Packet(Rsp6002& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("paginal_num"       , stBody.paginal_num);
		pkt.AddParameter("page_count"        , stBody.page_count);
		pkt.AddParameter("curr_page"         , stBody.curr_page);
		pkt.AddParameter("alm_result"        , stBody.alm_result);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    �����������ò�ѯ����������
	static int Packet2Struct(Req6005& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("report_id"         , stBody.report_id);
		pkt.GetParameterVal("c_rdlc_ver"        , stBody.c_rdlc_ver);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �����������ò�ѯ����������
	static int Struct2Packet(Req6005& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("report_id"         , stBody.report_id);
		pkt.AddParameter("c_rdlc_ver"        , stBody.c_rdlc_ver);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    �����������ò�ѯ����Ӧ������
	static int Packet2Struct(Rsp6005& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("report_id"         , stBody.report_id);
		pkt.GetParameterVal("report_name"       , stBody.report_name);
		pkt.GetParameterVal("cell_num"          , stBody.cell_num);
		pkt.GetParameterVal("cell_inv_width"    , stBody.cell_inv_width);
		pkt.GetParameterVal("cell_inv_height"   , stBody.cell_inv_height);
		pkt.GetParameterVal("s_rdlc_ver"        , stBody.s_rdlc_ver);
		pkt.GetParameterVal("alm_data_source"   , stBody.alm_data_source);
		pkt.GetParameterVal("alm_options"       , stBody.alm_options);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �����������ò�ѯ����Ӧ������
	static int Struct2Packet(Rsp6005& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("report_id"         , stBody.report_id);
		pkt.AddParameter("report_name"       , stBody.report_name);
		pkt.AddParameter("cell_num"          , stBody.cell_num);
		pkt.AddParameter("cell_inv_width"    , stBody.cell_inv_width);
		pkt.AddParameter("cell_inv_height"   , stBody.cell_inv_height);
		pkt.AddParameter("s_rdlc_ver"        , stBody.s_rdlc_ver);
		pkt.AddParameter("alm_data_source"   , stBody.alm_data_source);
		pkt.AddParameter("alm_options"       , stBody.alm_options);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ����Դ���ص���������
	static int Packet2Struct(Req6007& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("exch_date"         , stBody.exch_date);
		pkt.GetParameterVal("alm_ds_list"       , stBody.alm_ds_list);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����Դ���ص���������
	static int Struct2Packet(Req6007& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("exch_date"         , stBody.exch_date);
		pkt.AddParameter("alm_ds_list"       , stBody.alm_ds_list);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ����Դ���ص���Ӧ������
	static int Packet2Struct(Rsp6007& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"       , stBody.oper_flag);
		pkt.GetParameterVal("Title"                    , stBody.htm_Title);
		pkt.GetParameterVal("AcctSettleRisk"           , stBody.htm_AcctSettleRisk);
		pkt.GetParameterVal("AcctSettleFund"           , stBody.htm_AcctSettleFund);
		pkt.GetParameterVal("AcctSettleFundDetail"     , stBody.htm_AcctSettleFundDetail);
		pkt.GetParameterVal("AcctSettleStorage"        , stBody.htm_AcctSettleStorage);
		pkt.GetParameterVal("AcctSettleForward"        , stBody.htm_AcctSettleForward);
		pkt.GetParameterVal("AcctSettleDefer"          , stBody.htm_AcctSettleDefer);
		pkt.GetParameterVal("AcctSettleSurplus"        , stBody.htm_AcctSettleSurplus);
		pkt.GetParameterVal("AcctSettleMatchFlow"      , stBody.htm_AcctSettleMatchFlow);
		pkt.GetParameterVal("AcctSettleFundInOutFlow"  , stBody.htm_AcctSettleFundInOutFlow);

		pkt.GetParameterVal("TitleMonth"                    , stBody.htm_Title);
		pkt.GetParameterVal("AcctSettleRiskMonth"           , stBody.htm_AcctSettleRisk);
		pkt.GetParameterVal("AcctSettleFundMonth"           , stBody.htm_AcctSettleFund);
		pkt.GetParameterVal("AcctSettleFundDetailMonth"     , stBody.htm_AcctSettleFundDetail);
		pkt.GetParameterVal("AcctSettleStorageMonth"        , stBody.htm_AcctSettleStorage);
		pkt.GetParameterVal("AcctSettleDeferMonth"          , stBody.htm_AcctSettleDefer);
		pkt.GetParameterVal("AcctSettleSurplusMonth"        , stBody.htm_AcctSettleSurplus);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ����Դ���ص���Ӧ������
	static int Struct2Packet(Rsp6007& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"           , stBody.oper_flag);
		pkt.AddParameter("AcctSettleRisk"  , stBody.htm_AcctSettleRisk);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    �û���¼
	static int Packet2Struct(Req8001& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("user_type"         , stBody.user_type);
		pkt.GetParameterVal("user_id_type"      , stBody.user_id_type);
		pkt.GetParameterVal("user_id"           , stBody.user_id);
		pkt.GetParameterVal("user_pwd"          , stBody.user_pwd);
		pkt.GetParameterVal("login_ip"          , stBody.login_ip);
		pkt.GetParameterVal("ver_num"           , stBody.ver_num);
		pkt.GetParameterVal("is_down_para"      , stBody.is_down_para);
		pkt.GetParameterVal("bank_no"           , stBody.bank_no);
		pkt.GetParameterVal("login_server_code" , stBody.login_server_code);
		pkt.GetParameterVal("isSign"            , stBody.isSign);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �û���¼
	static int Struct2Packet(Req8001& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("user_type"         , stBody.user_type);
		pkt.AddParameter("user_id_type"      , stBody.user_id_type);
		pkt.AddParameter("user_id"           , stBody.user_id);
		pkt.AddParameter("user_pwd"          , stBody.user_pwd);
		pkt.AddParameter("login_ip"          , stBody.login_ip);
		pkt.AddParameter("ver_num"           , stBody.ver_num);
		pkt.AddParameter("is_down_para"      , stBody.is_down_para);
		pkt.AddParameter("bank_no"           , stBody.bank_no);
		pkt.AddParameter("login_server_code" , stBody.login_server_code);
		pkt.AddParameter("isSign"            , stBody.isSign);
		pkt.AddParameter("CN"            , stBody.CN);
		pkt.AddParameter("session_id"		, stBody.session_id);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    �û���¼��Ӧ������
	static int Packet2Struct(Rsp8001& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("check_code"        , stBody.check_code);
		pkt.GetParameterVal("member_id"         , stBody.member_id);
		pkt.GetParameterVal("member_name"       , stBody.member_name);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("branch_name"       , stBody.branch_name);
		pkt.GetParameterVal("acct_type"         , stBody.acct_type);
		pkt.GetParameterVal("user_id"           , stBody.user_id);
		pkt.GetParameterVal("user_name"         , stBody.user_name);
		pkt.GetParameterVal("sys_date"          , stBody.sys_date);
		pkt.GetParameterVal("exch_date"         , stBody.exch_date);
		pkt.GetParameterVal("exch_time"         , stBody.exch_time);
		pkt.GetParameterVal("last_exch_date"    , stBody.last_exch_date);
		pkt.GetParameterVal("version"           , stBody.version);
		pkt.GetParameterVal("m_sys_stat"        , stBody.m_sys_stat);
		pkt.GetParameterVal("b_sys_stat"        , stBody.b_sys_stat);
		pkt.GetParameterVal("first_login"       , stBody.first_login);
		pkt.GetParameterVal("need_change_pwd"   , stBody.need_change_pwd);
		pkt.GetParameterVal("last_login_date"   , stBody.last_login_date);
		pkt.GetParameterVal("last_login_time"   , stBody.last_login_time);
		pkt.GetParameterVal("last_lan_ip"       , stBody.last_lan_ip);
		pkt.GetParameterVal("last_www_ip"       , stBody.last_www_ip);
		pkt.GetParameterVal("exist_login"       , stBody.exist_login);
		pkt.GetParameterVal("no_affirm_rpt_num" , stBody.no_affirm_rpt_num);
		pkt.GetParameterVal("comp_stat"         , stBody.comp_stat);
		pkt.GetParameterVal("auto_entry_menu_id"         , stBody.auto_entry_menu_id);
		pkt.GetParameterVal("alm_menu_info"     , stBody.alm_menu_info);
		pkt.GetParameterVal("alm_cust_type_id"  , stBody.alm_cust_type_id);
		pkt.GetParameterVal("more_login_msg"  , stBody.more_login_msg);
		pkt.GetParameterVal("alm_take_man_list" , stBody.alm_take_man_list);
		pkt.GetParameterVal("alm_role_list"     , stBody.alm_role_list);
		pkt.GetParameterVal("alm_code_table_list", stBody.alm_code_table_list);
		pkt.GetParameterVal("alm_prod_code_list", stBody.alm_prod_code_list);
		pkt.GetParameterVal("alm_variety_list"  , stBody.alm_variety_list);
		pkt.GetParameterVal("alm_city_code_list", stBody.alm_city_code_list);
		pkt.GetParameterVal("alm_fare_type_list", stBody.alm_fare_type_list);
		pkt.GetParameterVal("alm_query_list"    , stBody.alm_query_list);
		pkt.GetParameterVal("alm_report_list"   , stBody.alm_report_list);
		pkt.GetParameterVal("alm_noread_bulletin_list", stBody.alm_noread_bulletin_list);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �û���¼��Ӧ������
	static int Struct2Packet(Rsp8001& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("check_code"        , stBody.check_code);
		pkt.AddParameter("member_id"         , stBody.member_id);
		pkt.AddParameter("member_name"       , stBody.member_name);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("branch_name"       , stBody.branch_name);
		pkt.AddParameter("acct_type"         , stBody.acct_type);
		pkt.AddParameter("user_id"           , stBody.user_id);
		pkt.AddParameter("user_name"         , stBody.user_name);
		pkt.AddParameter("sys_date"          , stBody.sys_date);
		pkt.AddParameter("exch_date"         , stBody.exch_date);
		pkt.AddParameter("exch_time"         , stBody.exch_time);
		pkt.AddParameter("last_exch_date"    , stBody.last_exch_date);
		pkt.AddParameter("version"           , stBody.version);
		pkt.AddParameter("m_sys_stat"        , stBody.m_sys_stat);
		pkt.AddParameter("b_sys_stat"        , stBody.b_sys_stat);
		pkt.AddParameter("first_login"       , stBody.first_login);
		pkt.AddParameter("need_change_pwd"   , stBody.need_change_pwd);
		pkt.AddParameter("last_login_date"   , stBody.last_login_date);
		pkt.AddParameter("last_login_time"   , stBody.last_login_time);
		pkt.AddParameter("last_lan_ip"       , stBody.last_lan_ip);
		pkt.AddParameter("last_www_ip"       , stBody.last_www_ip);
		pkt.AddParameter("exist_login"       , stBody.exist_login);
		pkt.AddParameter("no_affirm_rpt_num" , stBody.no_affirm_rpt_num);
		pkt.AddParameter("comp_stat"         , stBody.comp_stat);
		pkt.AddParameter("alm_menu_info"     , stBody.alm_menu_info);
		pkt.AddParameter("alm_cust_type_id"  , stBody.alm_cust_type_id);
		pkt.AddParameter("alm_take_man_list" , stBody.alm_take_man_list);
		pkt.AddParameter("alm_role_list"     , stBody.alm_role_list);
		pkt.AddParameter("alm_code_table_list", stBody.alm_code_table_list);
		pkt.AddParameter("alm_prod_code_list", stBody.alm_prod_code_list);
		pkt.AddParameter("alm_variety_list"  , stBody.alm_variety_list);
		pkt.AddParameter("alm_city_code_list", stBody.alm_city_code_list);
		pkt.AddParameter("alm_fare_type_list", stBody.alm_fare_type_list);
		pkt.AddParameter("alm_query_list"    , stBody.alm_query_list);
		pkt.AddParameter("alm_report_list"   , stBody.alm_report_list);
		pkt.AddParameter("alm_noread_bulletin_list", stBody.alm_noread_bulletin_list);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    �û��˳�
	static int Packet2Struct(Req8002& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("user_type"         , stBody.user_type);
		pkt.GetParameterVal("user_id"           , stBody.user_id);
		pkt.GetParameterVal("session_id"        , stBody.session_id);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �û��˳�
	static int Struct2Packet(Req8002& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("user_type"         , stBody.user_type);
		pkt.AddParameter("user_id"           , stBody.user_id);
		pkt.AddParameter("session_id"        , stBody.session_id);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    �û���¼��Ӧ������
	static int Packet2Struct(Rsp8002& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �û���¼��Ӧ������
	static int Struct2Packet(Rsp8002& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ��¼��֤
	static int Packet2Struct(Req8006& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("user_type"         , stBody.user_type);
		pkt.GetParameterVal("user_id_type"      , stBody.user_id_type);
		pkt.GetParameterVal("user_id"           , stBody.user_id);
		pkt.GetParameterVal("user_pwd"          , stBody.user_pwd);
		pkt.GetParameterVal("login_ip"          , stBody.login_ip);
		pkt.GetParameterVal("bank_no"           , stBody.bank_no);
		pkt.GetParameterVal("net_envionment"    , stBody.net_envionment);
		pkt.GetParameterVal("net_agent"         , stBody.net_agent);
		pkt.GetParameterVal("isSign"            , stBody.isSign);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ��¼��֤
	static int Struct2Packet(Req8006& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("user_type"         , stBody.user_type.c_str());
		pkt.AddParameter("user_id_type"      , stBody.user_id_type.c_str());
		pkt.AddParameter("user_id"           , stBody.user_id.c_str());
		pkt.AddParameter("user_pwd"          , stBody.user_pwd.c_str());
		pkt.AddParameter("login_ip"          , stBody.login_ip.c_str());
		pkt.AddParameter("bank_no"           , stBody.bank_no.c_str());
		pkt.AddParameter("net_envionment"    , stBody.net_envionment.c_str());
		pkt.AddParameter("net_agent"         , stBody.net_agent.c_str());
		pkt.AddParameter("isSign"            , stBody.isSign.c_str());
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ��¼��֤
	static int Packet2Struct(Rsp8006& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("session_id"        , stBody.session_id);
		pkt.GetParameterVal("session_key"       , stBody.session_key);
		pkt.GetParameterVal("server_code"       , stBody.server_code);
		pkt.GetParameterVal("server_name"       , stBody.server_name);
		pkt.GetParameterVal("trans_ip"          , stBody.trans_ip);
		pkt.GetParameterVal("trans_port"        , stBody.trans_port);
		pkt.GetParameterVal("query_ip"          , stBody.query_ip);
		pkt.GetParameterVal("query_port"        , stBody.query_port);
		pkt.GetParameterVal("broadcast_ip"      , stBody.broadcast_ip);
		pkt.GetParameterVal("broadcast_port"    , stBody.broadcast_port);
		pkt.GetParameterVal("risk_trans_ip"     , stBody.risk_trans_ip);
		pkt.GetParameterVal("risk_trans_port"   , stBody.risk_trans_port);
		pkt.GetParameterVal("risk_broadcast_ip" , stBody.risk_broadcast_ip);
		pkt.GetParameterVal("risk_broadcast_port", stBody.risk_broadcast_port);
		pkt.GetParameterVal("htm_server_list"   , stBody.htm_server_list);
		pkt.GetParameterVal("htm_more_login_list"   , stBody.htm_more_login_list);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ��¼��֤
	static int Struct2Packet(Rsp8006& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("session_id"        , stBody.session_id);
		pkt.AddParameter("session_key"       , stBody.session_key);
		pkt.AddParameter("server_code"       , stBody.server_code);
		pkt.AddParameter("server_name"       , stBody.server_name);
		pkt.AddParameter("trans_ip"          , stBody.trans_ip);
		pkt.AddParameter("trans_port"        , stBody.trans_port);
		pkt.AddParameter("query_ip"          , stBody.query_ip);
		pkt.AddParameter("query_port"        , stBody.query_port);
		pkt.AddParameter("broadcast_ip"      , stBody.broadcast_ip);
		pkt.AddParameter("broadcast_port"    , stBody.broadcast_port);
		pkt.AddParameter("risk_trans_ip"     , stBody.risk_trans_ip);
		pkt.AddParameter("risk_trans_port"   , stBody.risk_trans_port);
		pkt.AddParameter("risk_broadcast_ip" , stBody.risk_broadcast_ip);
		pkt.AddParameter("risk_broadcast_port", stBody.risk_broadcast_port);
		pkt.AddParameter("htm_server_list"   , stBody.htm_server_list);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ��¼��֤
	static int Packet2Struct(Req8007& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("user_type"         , stBody.user_type);
		pkt.GetParameterVal("user_id_type"      , stBody.user_id_type);
		pkt.GetParameterVal("user_id"           , stBody.user_id);
		pkt.GetParameterVal("user_pwd"          , stBody.user_pwd);
		pkt.GetParameterVal("login_ip"          , stBody.login_ip);
		pkt.GetParameterVal("bank_no"           , stBody.bank_no);
		pkt.GetParameterVal("isSign"            , stBody.isSign);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ��¼��֤
	static int Struct2Packet(Req8007& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("user_type"         , stBody.user_type);
		pkt.AddParameter("user_id_type"      , stBody.user_id_type);
		pkt.AddParameter("user_id"           , stBody.user_id);
		pkt.AddParameter("user_pwd"          , stBody.user_pwd);
		pkt.AddParameter("login_ip"          , stBody.login_ip);
		pkt.AddParameter("bank_no"           , stBody.bank_no);
		pkt.AddParameter("isSign"            , stBody.isSign);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ��¼��֤
	static int Packet2Struct(Rsp8007& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("succ"         , stBody.succ);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ��¼��֤
	static int Struct2Packet(Rsp8007& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("succ"        , stBody.succ);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    �����������ѯ����������
	static int Packet2Struct(Req8030& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("seq_no"            , stBody.seq_no);
		pkt.GetParameterVal("title"             , stBody.title);
		pkt.GetParameterVal("s_exch_date"       , stBody.s_exch_date);
		pkt.GetParameterVal("e_exch_date"       , stBody.e_exch_date);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �����������ѯ����������
	static int Struct2Packet(Req8030& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("seq_no"            , stBody.seq_no);
		pkt.AddParameter("title"             , stBody.title);
		pkt.AddParameter("s_exch_date"       , stBody.s_exch_date);
		pkt.AddParameter("e_exch_date"       , stBody.e_exch_date);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    �����������ѯ����Ӧ������
	static int Packet2Struct(Rsp8030& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("alm_result"        , stBody.alm_result);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    �����������ѯ����Ӧ������
	static int Struct2Packet(Rsp8030& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("alm_result"        , stBody.alm_result);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ��Ա�����ѯ����������
	static int Packet2Struct(Req8031& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("bulletin_id"       , stBody.bulletin_id);
		pkt.GetParameterVal("title"             , stBody.title);
		pkt.GetParameterVal("s_exch_date"       , stBody.s_exch_date);
		pkt.GetParameterVal("e_exch_date"       , stBody.e_exch_date);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ��Ա�����ѯ����������
	static int Struct2Packet(Req8031& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("bulletin_id"       , stBody.bulletin_id);
		pkt.AddParameter("title"             , stBody.title);
		pkt.AddParameter("s_exch_date"       , stBody.s_exch_date);
		pkt.AddParameter("e_exch_date"       , stBody.e_exch_date);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ��Ա�����ѯ����Ӧ������
	static int Packet2Struct(Rsp8031& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("alm_result"        , stBody.alm_result);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ��Ա�����ѯ����Ӧ������
	static int Struct2Packet(Rsp8031& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("alm_result"        , stBody.alm_result);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ���������ѯ����������
	static int Packet2Struct(Req9010& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("is_contain_self"   , stBody.is_contain_self);
		pkt.GetParameterVal("bank_no"           , stBody.bank_no);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ���������ѯ����������
	static int Struct2Packet(Req9010& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("is_contain_self"   , stBody.is_contain_self);
		pkt.AddParameter("bank_no"           , stBody.bank_no);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ���������ѯ����Ӧ������
	static int Packet2Struct(Rsp9010& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("branch_name"       , stBody.branch_name);
		pkt.GetParameterVal("branch_level"      , stBody.branch_level);
		pkt.GetParameterVal("parent_branch_id"  , stBody.parent_branch_id);
		pkt.GetParameterVal("bank_no"           , stBody.bank_no);
		pkt.GetParameterVal("city_code"         , stBody.city_code);
		pkt.GetParameterVal("is_self_bank"      , stBody.is_self_bank);
		pkt.GetParameterVal("htm_branch_info"   , stBody.htm_branch_info);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ���������ѯ����Ӧ������
	static int Struct2Packet(Rsp9010& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("branch_name"       , stBody.branch_name);
		pkt.AddParameter("branch_level"      , stBody.branch_level);
		pkt.AddParameter("parent_branch_id"  , stBody.parent_branch_id);
		pkt.AddParameter("bank_no"           , stBody.bank_no);
		pkt.AddParameter("city_code"         , stBody.city_code);
		pkt.AddParameter("is_self_bank"      , stBody.is_self_bank);
		pkt.AddParameter("htm_branch_info"   , stBody.htm_branch_info);
		return 0;
	};



	// ���Ľ��������� -> �ṹ    ϵͳ����������������
	static int Packet2Struct(Req9030& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("para_id"           , stBody.para_id);
		pkt.GetParameterVal("para_type"         , stBody.para_type);
		pkt.GetParameterVal("para_desc"         , stBody.para_desc);
		pkt.GetParameterVal("para_value"        , stBody.para_value);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    ϵͳ����������������
	static int Struct2Packet(Req9030& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("para_id"           , stBody.para_id);
		pkt.AddParameter("para_type"         , stBody.para_type);
		pkt.AddParameter("para_desc"         , stBody.para_desc);
		pkt.AddParameter("para_value"        , stBody.para_value);
		return 0;
	};

	// ���Ľ��������� -> �ṹ    ϵͳ����������Ӧ������
	static int Packet2Struct(Rsp9030& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("para_id"           , stBody.para_id);
		pkt.GetParameterVal("para_type"         , stBody.para_type);
		pkt.GetParameterVal("para_desc"         , stBody.para_desc);
		pkt.GetParameterVal("para_value"        , stBody.para_value);
		pkt.GetParameterVal("htm_para_info"     , stBody.htm_para_info);
		return 0;
	};

	// ���Ľ����� �ṹ -> ����    ϵͳ����������Ӧ������
	static int Struct2Packet(Rsp9030& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("para_id"           , stBody.para_id);
		pkt.AddParameter("para_type"         , stBody.para_type);
		pkt.AddParameter("para_desc"         , stBody.para_desc);
		pkt.AddParameter("para_value"        , stBody.para_value);
		pkt.AddParameter("htm_para_info"     , stBody.htm_para_info);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    ����ȡ����������
	static int Struct2Packet(Req4074& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("start_date"         , stBody.start_date);
		pkt.AddParameter("end_date"         , stBody.end_date);
		pkt.AddParameter("acct_no"         , stBody.acct_no);
		pkt.AddParameter("delegate_type"         , stBody.delegate_type);
		pkt.AddParameter("src_match_no"         , stBody.src_match_no);
		pkt.AddParameter("trigger_status"         , stBody.trigger_status);
		pkt.AddParameter("serial_no"         , stBody.serial_no);
		pkt.AddParameter("exch_type"         , stBody.exch_type);
		pkt.AddParameter("prod_code"         , stBody.prod_code);
		pkt.AddParameter("entr_price"         , stBody.entr_price);
		pkt.AddParameter("entr_amount"         , stBody.entr_amount);
		pkt.AddParameter("entr_price_type"         , stBody.entr_price_type);
		pkt.AddParameter("trigger_condition"         , stBody.trigger_condition);
		pkt.AddParameter("trigger_value_type"         , stBody.trigger_value_type);
		pkt.AddParameter("trigger_value"         , stBody.trigger_value);
		pkt.AddParameter("base_adjust_step"         , stBody.base_adjust_step);
		pkt.AddParameter("entr_adjust_step"         , stBody.entr_adjust_step);

		return 0;
	};

	// ���Ľ��������� -> �ṹ    ����ȡ����Ӧ������
	static int Packet2Struct(Rsp4074& stBody, CTradePacket& pkt)
	{
		Packet2StructBase(stBody, pkt);
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("alm_result"         , stBody.alm_result);

		return 0;
	};
};
