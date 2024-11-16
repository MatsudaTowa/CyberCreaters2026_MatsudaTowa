//=============================================
//
//3DTemplate[enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "block.h"
#include "field.h"
#include "camera.h"
#include "game.h"
#include "wave.h"
#include "player_test.h"

//�G�l�~�[����
int CEnemy::m_NumEnemy = 0;

//�ʏ�̈ړ����x
const float CEnemy::DEFAULT_MOVE = 1.0f;
//�ʏ�̈ړ����x
const float CEnemy::DAMPING_COEFFICIENT = 0.3f;

//�ʏ�̃W�����v��
const float CEnemy::DEFAULT_JUMP = 25.0f;

//�����艺�ɍs�����玀�ʍ��W
const float CEnemy::DEADZONE_Y = -100.0f;

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CEnemy::m_pTextureTemp = nullptr;

LPD3DXBUFFER CEnemy::m_pBuffMat = nullptr;

LPD3DXMESH CEnemy::m_pMesh = nullptr;

DWORD CEnemy::m_dwNumMat = 0;

//=============================================
//�R���X�g���N�^
//=============================================
CEnemy::CEnemy(int nPriority) :CCharacter(nPriority)
, m_Motion(),m_Type()
{//�C�j�V�����C�U�[�Ń����o�ϐ�������
	//�����ǉ�
	m_NumEnemy++;
	if (m_pMove == nullptr)
	{
		m_pMove = new CEnemyMove;
	}
	if (m_pAttack == nullptr)
	{
		m_pAttack = new CEnemyAttack;
	}
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemy::~CEnemy()
{
	//��������
	m_NumEnemy--;
}

//=============================================
//������
//=============================================
HRESULT CEnemy::Init()
{
	CCharacter::Init();

	//�e������
	if (m_pGun == nullptr)
	{
		m_pGun = new CAssultRifle;

		m_pGun->Init();
	}

	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//�ړ��ʏ�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���[�u�l���
	SetMove(move);

	Load_Parts("data\\Motion.txt");

	m_Motion = CEnemy::Motion_Type::MOTION_MAX; //�j���[�g�����ɐݒ�

	SetMotion(MOTION_NEUTRAL);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CEnemy::Uninit()
{
	//�e�N���X�̏I���������Ă�
	CCharacter::Uninit();

}

//=============================================
//�X�V
//=============================================
void CEnemy::Update()
{
	CCharacter::Update();

	m_pCharacterState->Move(this);

	m_pCharacterState->Shot(CBullet::BULLET_ALLEGIANCE_ENEMY, CBullet::BULLET_TYPE_NORMAL,this);

	//���݂̃V�[�����擾
	CScene::MODE pScene = CScene::GetSceneMode();

	if (pScene != CScene::MODE::MODE_TITLE)
	{
		//�_���[�W�X�e�[�g�̐؂�ւ�TODO:������X�e�[�g�p�^�[����
		ChangeDamageState();

		//�Q�[���̏�Ԏ擾
		CGame::GAME_STATE Game_state = CGame::GetState();

		if (GetPos().y < DEADZONE_Y)
		{//���X�|�[������
			ReSpawn();
		}

		//�ǂ��������Ă邩�擾
		bool bWay = GetWay();

		Motion(NUM_PARTS); //���[�V��������
	}
}

//=============================================
//�`��
//=============================================
void CEnemy::Draw()
{
	//�e�N���X�̃��[�V�����p�̕`����Ă�
	MotionDraw(NUM_PARTS, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
}

//=============================================
//����
//=============================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const ENEMY_TYPE& type)
{
	CEnemy* pEnemy = new CEnemy;

	// null�Ȃ�null��Ԃ�
	if (pEnemy == nullptr) { return nullptr; }

	pEnemy->m_Type = type;
	pEnemy->SetPos(pos); //pos�ݒ�
	pEnemy->SetRot(rot); //rot�ݒ�
	pEnemy->SetLife(DEFAULT_LIFE); //�̗͑��

	pEnemy->Init(); //����������

	pEnemy->SetType(OBJECT_TYPE_ENEMY); //�^�C�v�ݒ�

	return pEnemy;
}

//=============================================
//�_���[�W���󂯂��Ƃ�
//=============================================
void CEnemy::Damage(int nDamage)
{
	//�̗͎擾
	int nLife = GetLife();
	//��Ԃ��擾
	CCharacter::CHARACTER_STATE state = GetState();

	if (nLife > 0 && state != CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{//�_���[�W��ԈȊO��HP���c���Ă���
		nLife -= nDamage;

		//�_���[�W��ԂɕύX
		state = CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE;

		//��ԑ��
		SetState(state);

		//�̗͑��
		SetLife(nLife);
	}
	if (nLife <= 0)
	{//HP��0�ȉ���������
		CScore* pScore = CWave::GetScore();

		int nAddScore = 0;
		switch (m_Type)
		{
		case CEnemy::ENEMY_TYPE::ENEMY_TYPE_NORMAL:
			nAddScore = 300;
			break;
		default:
			assert(false);
			break;
		}
		pScore->AddScore(nAddScore);
		//�I��
		Uninit();
	}
}

//=============================================
//���X�|�[��
//=============================================
void CEnemy::ReSpawn()
{
	//�������g��pos�擾
	D3DXVECTOR3 EnemyPos = GetPos();

	EnemyPos = D3DXVECTOR3(-450.0f, 0.5f, 0.0f);

	//pos���
	SetPos(EnemyPos);
}

//=============================================
//�_���[�W�X�e�[�g�̐؂�ւ�
//=============================================
void CEnemy::ChangeDamageState()
{
	//��Ԃ��擾
	CCharacter::CHARACTER_STATE state = GetState();

	if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		//��Ԃ̃J�E���g���擾
		int nStateCnt = GetStateCnt();

		//�X�e�[�g�ύX�J�E���g�i�߂�
		nStateCnt++;

		if (nStateCnt >= 10)
		{
			//�ʏ�ɖ߂�
			state = CCharacter::CHARACTER_STATE::CHARACTER_NORMAL;

			//�X�e�[�g�J�E���g���Z�b�g
			nStateCnt = 0;

			//��ԑ��
			SetState(state);
		}

		//�X�e�[�g�J�E���g���
		SetStateCnt(nStateCnt);
	}
}