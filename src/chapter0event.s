@by laqieer
@2017/04/24
@���¾����¼�(������)

	.include	"FE7JEvent.inc"
	.include	"FE7JCharacterList.inc"
	.include	"FE7JClassList.inc"
	.include	"FE7JItemList.inc"

	.section	.rodata
	.align		4
	.global		chapter0event
chapter0event:
	.word		turnEvents		@ �غ��¼�
	.word		talkEvents		@ �Ự�¼�
	.word		locationEvents	@ λ���¼�
	.word		miscEvents		@ �����¼�
	.word		trapDataE, trapDataH	@ ���ز���
	.word		enemiesEN, enemiesEH, enemiesHN, enemiesHH	@ �з�����
	.word		alliesEN,	alliesEH,	alliesHN, alliesHH	@ �ҷ�����
	.word		openingEvent, endingEvents	@ �½ڿ�ͷ�ͽ�β

openingEvent:
@	.word		cameraOff
@	.word		loadUnits,	enemiesEN
@	.word		wait
@	.word		call,	0x807B3AC+1
@	.word		call,	0x807B448+1
	cameraOff
	loadUnits	enemiesEN
	wait
	call	0x807B3AC
	call	0x807B448
	fadeInCG
	
	

enemiesEN:
enemiesEH:
enemiesHN:
enemiesHH:
	@��ʽ: ����	ְҵ	�ӳ�	�ȼ��������Զ��ȼ�	��ʼλ��	�յ�λ��	Я����Ʒ1		Я����Ʒ2		Я����Ʒ3		Я����Ʒ4		AI1	AI2	AI3	AI4
	.byte	Batta,	Brigand,	0,	2*8+2*2+0,				3,2,		3,2,		IronAxe,		0,				0,				0,				3,		3,		9,		0x20	@ boss����
	.byte	Bandit,Brigand,Batta,1*8+2*2+0,			2,6,		2,6,		IronAxe,		0,				0,				0,				0,		0,		9,		0		@ �ӱ�ɽ��
	endList

turnEvents:

talkEvents:

locationEvents:

miscEvents:

trapDataE:
trapDataH:

alliesEN:
alliesEH:
alliesHN:
alliesHH:

endingEvents:
