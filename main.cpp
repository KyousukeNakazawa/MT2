#include "DxLib.h"
//#include "Vector2.h"
#include "Vector3.h"

//�֐��v���g�^�C�v
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color);

int SetCameraPositionAndTragetAndUpVec(const Vector3& cameraPos, const Vector3& cameraTarget, const Vector3& cameraUp);

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "GC1A_15_�i�J�U���L���E�X�P: �^�C�g��";

// �E�B���h�E����
const int WIN_WIDTH = 1024;

// �E�B���h�E�c��
const int WIN_HEIGHT = 576;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	//�N���b�v�ʁ@�߁@��
	SetCameraNearFar(1.0f, 1000.0f);	//�J�����̗L���͈͂�ݒ�
	SetCameraScreenCenter(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f);	//��ʂ̒��S�ɃJ�����̒��S�����킹��
	Vector3 cameraPosition(0.0f, 0.0f, -30.0f);
	Vector3 cameraTarget(0.0f, 0.0f, 0.0f);
	Vector3 cameraUp(0.0f, 1.0f, 0.0f);
	SetCameraPositionAndTragetAndUpVec(
		cameraPosition, cameraTarget, cameraUp
	);

	Vector3 A(3, -1, 2);
	Vector3 B(1, 5, -4);
	Vector3 C(-1, 7, 6);

	Vector3 AB = B - A;
	Vector3 AC = C - A;
	Vector3 BC = C - B;
	Vector3 BA = A - B;
	Vector3 CA = A - C;
	Vector3 CB = B - C;

	Vector3 n = AB;
	n.Cross(BC);
	n.Normalize();

	Vector3 position(0, 0, 0);				//�ʒu
	Vector3 velocity(0.0f, 0.0f, 0.5f);		//���x
	SetUseZBufferFlag(TRUE);
	SetWriteZBufferFlag(TRUE);

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; ++i) {
			oldkeys[i] = keys[i];
		}

		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		Vector3 g = (A + B + C) / 3;
		Vector3 v = cameraPosition - g;
		v.Normalize();

		unsigned color = GetColor(255, 255, 255);

		if (v.Dot(n) > 0) {
			color = GetColor(255, 0, 0);
		}

		//�`��
		ClearDrawScreen();	//��ʂ�����
		DrawLine3D(A, B, color);
		DrawLine3D(B, C, color);
		DrawLine3D(C, A, color);


		Vector3 nA = n + (A - g);
		Vector3 nB = n + (B - g);
		Vector3 nC = n + (C - g);

		DrawLine3D(A, nA, 0x00ff00);
		DrawLine3D(B, nB, 0x00ff00);
		DrawLine3D(C, nC, 0x00ff00);

		//DrawSphere3D(position, 80.0f, 32, 0xff0000, 0xffffff, true);

		/*Vector2 a(3, 2);
		Vector2 b(-2, 4);

		Vector2 a1 = a + b;
		Vector2 a2 = a - b;
		Vector2 a3 = 2 * a;
		Vector2 a4 = a - 2 * b;

		DrawFormatString(10, 10, 0xffffff, "a1.x%f a1.y:%f a2.x:%f a2.y%f", a1.x, a1.y, a2.x, a2.y);*/

		// �`�揈��
		//DrawCircle(position, 16, GetColor(128, 255, 128));

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}

//�I�[�o�[���[�h�֐�
////�\���ʒu�Ƀx�N�g�����w��ł���悤�ɂ���
//int DrawCircle(Vector2 vec, int r, unsigned int color) {
//	return DrawCircle(static_cast<int>(vec.x), static_cast<int>(vec.y), r, color);
//}

int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag) {
	VECTOR centerPos = { CenterPos.x, CenterPos.y, CenterPos.z };

	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);
}

int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color) {
	VECTOR p1 = { Pos1.x, Pos1.y, Pos1.z };
	VECTOR p2 = { Pos2.x, Pos2.y, Pos2.z };

	return DrawLine3D(p1, p2, Color);
}

//DxLib => int SetCameraPositionAndTragetAndUpVec(VECTOR Position, VECTOR Target, VECTOR Up);
int SetCameraPositionAndTragetAndUpVec(const Vector3& cameraPos, const Vector3& cameraTarget, const Vector3& cameraUp) {
	VECTOR position = { cameraPos.x, cameraPos.y, cameraPos.z };
	VECTOR target = { cameraTarget.x, cameraTarget.y, cameraTarget.z };
	VECTOR up = { cameraUp.x, cameraUp.y, cameraUp.z };

	return SetCameraPositionAndTargetAndUpVec(position, target, up);
}