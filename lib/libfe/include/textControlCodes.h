// by laqieer
// 2017/4/19
// �ı����Ʒ�

#pragma once

/* ���ֺ궨�巽ʽ�Ƚ�
	#define loadFace 0x10
	#define loadFace	'\x10'
	#define loadFace	"\x10"
	*/

// �������Ʒ�

// ����(�ַ�����β�Զ����)
#define end				"\0"
// ����
#define endl			"\x01"
// ��2��
#define endl2			"\x02"
// A��
#define pushA			"\x03"
// ��ͣ��
#define	shortPause		"\x04"
// ͣ��
#define pause			"\x05"
// ��ͣ��
#define longPause		"\x06"
// ����ͣ��
#define longlongPause	"\x07"
// �򿪶Ի���(�в�ͬλ��)
#define openLeft		"\x0a"
#define openRight		"\x0b"
#define openMidLeft		"\x09"
#define openMidRight	"\x0c"
#define openFarLeft		"\x08"
#define	openFarRight	"\x0d"
#define openFarFarLeft	"\x0e"
#define openFarFarRight	"\x0f"
// ����ͷ��
#define loadFace		"\x10"
// ���ͷ��
#define clearFace		"\x11"
// ���ٹرնԻ���
#define closeFast		"\x14"
// ���ٹرնԻ���
#define closeSlow		"\x15"
// ��ʼ/ֹͣ����
#define toggleMouthMove	"\x16"
// ��ʼ/ֹͣ΢Ц
#define toggleSmile		"\x17"
// ����ѡ��(Ĭ����)
#define	yes				"\x18"
// ����ѡ��(Ĭ�Ϸ�)
#define	no				"\x19"
// ����ѡ��(��/��)
#define buySell			"\x1a"
// ��ѡ�е�����ѹ���·�ͼ����ʾ
#define sendToBack		"\x1c"
// ��ͣ��(������Ч����)
#define	shortPauseWithSFX	"\x1f"

// ��չ���Ʒ�

// �������ͼ����ͷ��
#define	loadOverworldFace	"\x80\x04"
// ��ӡ�����
#define	goldAmount			"\x80\x05"
// �ƶ�ͷ��
#define	movetoLeft			"\x80\x0c"
#define	movetoRight			"\x80\x0d"
#define movetoMidLeft		"\x80\x0b"
#define movetoMidRight		"\x80\x0e"
#define movetoFarLeft		"\x80\x0a"
#define movetoFarRight		"\x80\x0f"
#define movetoFarFarLeft	"\x80\x10"
#define movetoFarFarRight	"\x80\x11"
// ʹ��գ��
#define enableBlinking		"\x80\x16"
// һ�н�������ʱһ��ʱ��գ��
#define delayBlinking		"\x80\x18"
// ��ʱ����ͣգ��
#define pauseBlinking		"\x80\x19"
// ��ֹգ��
#define disableBlinking		"\x80\x1b"
// ����
#define openEyes			"\x80\x1c"
// ����
#define closeEyes			"\x80\x1d"
// �����
#define halfCloseEyes		"\x80\x1e"
// գ������(ʹ��ɫ)
#define wink				"\x80\x1f"
// ��ӡ��ʦ����
#define tacticianName		"\x80\x20"
// �л��ı���ɫ(��ɫ�ͺ�ɫ)
#define toggleRed			"\x80\x21"
// ��ʾ��ǰ����Ʒ��
#define itemName			"\x80\x22"
// ��ʾ˵��������(�ı������ϵ�С��)(������CG�ĶԻ���������ƪ���¿�ͷ)
#define setName				"\x80\x23"
// �л��Ի���ɫ(Ӫ��ֲ�����)
#define	toggleColorInvert	"\x80\x25"

// ˭˵ʲô�� ��װ
// #define talk(portraitID,position,content)	open##position loadFace #portraitID endl content clearFace
// ���ͷ��궨��
#define sbsaysth(portrait,position,content)	open##position loadFace portrait endl content clearFace

