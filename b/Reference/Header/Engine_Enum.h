#ifndef Engine_Enum_h__
#define Engine_Enum_h__
#include "dinput.h"
namespace Engine
{
	enum WINMODE { MODE_FULL, MODE_WIN };

	// Dynamic ������Ʈ ��� �� �����Ӹ��� �����ؾ��ϴ� ������Ʈ ����
	enum COMPONENTID { ID_DYNAMIC, ID_STATIC, ID_END };

	enum INFO {	INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS, INFO_END };
	enum ROTATION { ROT_X, ROT_Y, ROT_Z, ROT_END };

	enum TEXTUREID { TEX_NORMAL, TEX_CUBE, TEX_END };

	enum RENDERID { RENDER_PRIORITY, RENDER_NONALPHA, RENDER_ALPHA, RENDER_UI, RENDER_TRANSLUCNET, RENDER_END };

	enum MOUSEKEYSTATE { DIM_LB, DIM_RB, DIM_MB, DIM_END };
	enum MOUSEMOVESTATE {	DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };

	// 09.19 ������
	enum PIPEFLOW { FLOW_UP, FLOW_DOWN, FLOW_LEFT, FLOW_RIGHT, FLOW_END };

	enum CHANNELID
	{
		SOUND_BGM,
		SOUND_EFFECT,
		SOUND_MOREEFFECT,
		SOUND_SURROUNDING,
		SOUND_NATURAL,
		SOUND_ElectricEel,	
		SOUND_ElectricEel_Collision,
		SOUND_RHINO,
		SOUND_STONE,
		MAXCHANNEL=32,
	};

	enum TAG { TAG_PLAYER, TAG_ENEMY, TAG_STONE, TAG_OBJECT, TAG_NONE };
	//0927 ������
	enum TEXTRANGE { TEXT_DEFAULT, TEXT_CENTER, TEXTRANGE_END };

	// 09.24 �輱ȯ
	enum GROUP_TYPE { PLAYER, MONSTER, OBJECT, NPC, PUZZLE, MONSTER_EFFECT, NATURAL, GROUP_END = 32 };

	enum GAME_STATE
	{
		GAMESTATE_NPCTALK,
		GAMESTATE_UIOPEN,
		GAMESTATE_EXPLAINATION,
		GAMESTATE_EVENTSCENE,
		GAMESTATE_NONE,
	};
	// 09.28 ����
	enum OBJ_TYPE
	{
		NOTPASS_ABLE = 1, // ������ �ش� �ɼ��� ���� ������Ʈ�� ����� �� �����ϴ�.
		PUSH_ABLE = 2,    // ������ �ش� �ɼ��� ���� ������Ʈ�� �� �� �ֽ��ϴ�.
		LIFT_ABLE = 4,    // ������ �ش� �ɼ��� ���� ������Ʈ�� �� �� �ֽ��ϴ�.
		DESTROY_ABLE = 8, // ������ �ش� �ɼ��� ���� ������Ʈ�� ���� �� �ֽ��ϴ�.
		TALK_ABLE = 16,   // ������ �ش� �ɼ��� ���� ������Ʈ�� ��ȭ�� �� �� �ֽ��ϴ�.
		HURT_ABLE = 32,   // ������ �ش� �ɼ��� ���� ������Ʈ���� ���ظ� ���� �� �ֽ��ϴ�.
		PICK_ABLE = 64,   // ������ �ش� �ɼ��� ���� ������Ʈ�� ������ �� �ֽ��ϴ�.
		TYPE_NONE = 128,
		TYPE_END
	};

	enum CONTROLKEY
	{
		PLY_LEFTKEY		= DIK_LEFT,
		PLY_RIGHTKEY	= DIK_RIGHT,
		PLY_UPKEY		= DIK_UP,
		PLY_DOWNKEY		= DIK_DOWN,
		PLY_DASHKEY		= DIK_LSHIFT,
		PLY_SWINGKEY	= DIK_A,
		PLY_LIFTKEY		= DIK_S,
		PLY_PICKUPKEY	= DIK_S,
		PLY_ROLLKEY		= DIK_D,
		PLY_DANCEKEY	= DIK_Q,
		PLY_SMASHKEY	= DIK_E,
		PLY_ENDKEY		= 11 // Ű �߰� �ϸ� ���ڵ� �÷��ּ���
	};

	// �ൿ ���� ����, DIAGONAL�� ���� �ൿ ������ ���� ��
	enum PLAYERSTATE
	{
		PLY_IDLE, PLY_IDLEDIAGONAL,
		PLY_MOVE, PLY_MOVEDIAGONAL,
		PLY_DASH, PLY_DASHDIAGONAL,
		PLY_SWING, PLY_SWINGDIAGONAL,
		PLY_IDLEDANCE,
		PLY_PUSH,

		PLY_LIFTSTART,
		PLY_LIFTIDLE,
		PLY_LIFTMOVE, PLY_LIFTMOVEDIAGONAL,
		PLY_LIFTEND,

		PLY_DANCE,
		PLY_SMASH, PLY_SMASHDIAGONAL,
		PLY_ROLLING, PLY_ROLLINGDIAGONAL,
		PLY_HURT, PLY_HURTDIAGOANL,
		PLY_BALLOONFLYUP, PLY_BALLOONFLYDOWN,
		PLY_PICKUP,
		PLY_END
	};


	// ���� �������� �� ��
	enum OBJ_DIRECTION
	{
		OBJDIR_FRONT = 1,
		OBJDIR_BACK = 2,
		OBJDIR_LEFT = 4,
		OBJDIR_RIGHT = 8,

		OBJDIR_LEFTFRONT = 5,
		OBJDIR_LEFTBACK = 6,
		OBJDIR_RIGHTFRONT = 9,
		OBJDIR_RIGHTBACK = 10,

		OBJDIR_NONE = 0,
		OBJDIR_END
	};
}
#endif // Engine_Enum_h__
