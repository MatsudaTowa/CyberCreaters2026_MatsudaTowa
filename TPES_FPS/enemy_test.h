//=============================================
//
//3DTemplate[enemy_test.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ENEMY_TEST_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ENEMY_TEST_H_
#include "main.h"
#include "model_parts.h"
#include "character.h"
//�G�l�~�[�N���X
class CEnemy_test :public CCharacter
{
public:
	static const int NUM_PARTS = 10; //�p�[�c��
	static const int MAX_KEY = 20; //�L�[�ő吔
	static const int NUM_MOTION = 3;
	static const int ENEMY_PRIORITY = 8; //�`�揇
	static const int PARTS_PARENT[NUM_PARTS]; //�p�[�c��

	CEnemy_test(int nPriority = ENEMY_PRIORITY);
	~CEnemy_test();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	//�G�l�~�[�쐬
	static CEnemy_test* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);

	void Damage(int nDamage); //�����蔻��

	static int m_NumEnemy; //�G�l�~�[�̑���

private:

	//�v���C���[�̈ړ��֘A
	static const float DEFAULT_MOVE; //�ʏ펞�̈ړ�
	static const float DAMPING_COEFFICIENT; //�ړ���R
	static const float DEFAULT_JUMP; //�ʏ펞�̃W�����v��
	static const int MAX_JUMPCNT; //�W�����v��
	static const int NUM_MOTION; //���[�V�����̐�
	static const float DEADZONE_Y; //������߂�����v���C���[�j��

	void ReSpawn(); //���X�|�[��
	void Move(); //�v���C���[�ړ�����

	int m_nJumpCnt; //�W�����v�J�E���g

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh;
	static 	LPD3DXBUFFER m_pBuffMat; //�}�e���A�����
	static	DWORD m_dwNumMat; //�}�e���A����

	//���[�V�����̎�ނ̗�
	typedef enum
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_MAX,
	}Motion_Type;

	Motion_Type m_Motion; //���[�V�����̎��

};
#endif