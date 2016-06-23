/**
    @file    variables.c
    @author  ���������� �.�. ��� "��� ��������", ���
    @date    01.03.2015
    @brief   ���� � ��������� ���������� ���������
    � ������ ����� ���������� �������� ���������� ���������. ��� ��� �������� ����������� �.�. ��� ������ ��������� �������������� ������ ����������������
    � �������� ����� �� ��������� ��������� ���������� � ���������� �� ����� � �����������. ��� �� ������������ �������������� ������������� ��������� ����������.
**/


uint8_t address=0;		//����� ����������
uint8_t channel=0;		//��������� �����
uint8_t firststart;		//������� �� ������� ������
uint8_t EnableRF=0;		//������� ��������� �������� ����������� (���������� ��� ���������)

uint8_t blinkmode=0;
uint16_t Vpower=0;		//���������� �������
uint8_t	PowerCode=0x60;		//����� ������������ � ���������
uint16_t Vspusk=0;		//���������� ���������� �����
uint16_t Vplank=0;		//���������� ���������� ������
uint16_t Vgnd=0;			//���������� ���� (���������)
uint16_t Vtemp=0;		//��������� ���������� ��� ���
uint8_t ADCmode=0;		//����� ������ ���
uint8_t StrikerStartPosition;	//�������� ����������� ��������� ��������

double ggx=0;
double ggy=0;
double ggz=0;

uint8_t cartrage=0;		//��������
uint8_t grenade=0;		//�������
uint8_t powermode=0;
uint8_t ammo=0;			//����������� � ��������
uint8_t PowerOn=0;              //�������� �������/��������
uint8_t LaserOn=0;		//����� �������/��������
uint8_t GameOn=0;		//��������� ��� ��� � �������
uint16_t KlapanOnTime=KLAPAN_ON_TIME;	//����� �������� �������
uint16_t PauseTime=KLAPAN_OFF_TIME;      //����� ����� �������
uint16_t StartSpusk=SPUSK_START_VALUE;	//��������� ��� ������ ������� ���������� ������
uint16_t FireSpusk=SPUSK_FIRE_VALUE;	//��������� ��� ������������ ��������
uint8_t minPlank=PLANK_MIN_VALUE;	//��������� ��� ��� ������������ ��������� ���������� ������ (��� �������, ��� �����������)
uint8_t maxPlank=PLANK_MAX_VALUE;	//��������� ��� ��� ������������� ��������� ���������� ������ (��� �������, ��� �����������)
uint16_t FireTimer;			//������� ������� ��������� �������
uint16_t FireDelay;			//������� ������� ��������� �������

uint8_t DataFromRF[DataSizeFromRF];	//����� � ��������� ������� ��� ������ ���������
uint8_t tmpDataFromRF[DataSizeFromRF];	//����� � ��������� ������� �������� ���������
uint8_t DataToRF[DataSizeToRF];		//����� � �������

uint8_t SizeFromCC;		//�����, ���������� � ��1101
uint8_t tmp;			//��������� ����������
uint8_t command_flag;		//������� ��������� �������
uint16_t CRC16;			//��, ��� �� ���� ���������
uint16_t tmpCRC16;		//��, ��� ��� ��������
uint16_t tmpQ;			//����� ���������� �������� RSSI � LQI

uint32_t timer=0;		//��� ������ � ����� 1�� (��� ��������� ������� ������� ���������� ������)
uint8_t	 timerEnable=0;		//���������� ������ ������� ������� ���������� ������
uint8_t FireStatus=0;		//��������� (����) ��������� ������������ ��������		
uint8_t lastFireStatus=0;
uint8_t AmmoInTrunk=0;		//������ � ����������
uint8_t FiredAmmoCount=0;	//���-�� ������������� ���������
uint8_t EventFire=0;		//������� ��������
uint16_t CartrageStatus=0;      //��������� ���������� ��������� ��������
uint8_t CartrageArray[31];     //���������� ���������
uint8_t Cartrages=MAXCARTRAGE;		//���-�� ��������� �� ���������
uint8_t CartrageCurrent=1;	//����� �������� ��������
uint8_t CartrageTrigger=0;      //��������� ��������

signed int gxraw = 0;		//
signed int gyraw = 0;		//
signed int gzraw = 0;		//����������� ��������
double gx = 0;			//
double gy = 0;			//
double gz = 0;			//

float PositionX=0;		//
float PositionX2=0;		//
float angleX=0;			//
float PositionY=0;		//
float PositionY2=0;		//����������� ���������
float angleY=0;			//
float PositionZ=0;		//
float PositionZ2=0;		//
float angleZ=0;			//

uint16_t EEcount=0;
uint16_t xx1=0x30;


uint8_t		eprom	EEPROM_SECTION  = 0;	//����� ������ � eeprom
