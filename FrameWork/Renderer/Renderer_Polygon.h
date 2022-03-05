//=============================================================================
//
//  �|���S���`��@�\ [Renderer_Polygon.h]
//  Date   : 2021/11/02
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../System/Main.h"
#include "../Renderer/Renderer_DirectX11.h"
#include "../System/Singleton.h"

//=============================================================================
//�@�萔�錾
//=============================================================================
constexpr float MAX_CUT_START_POSTION = 1.0f;//�ő�؂�����W

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct 
{
	int     AnimCount;        //���݂̃t���[����
	int     MaxAnimCount;     //���t���[���ōX�V���邩

	Vector2 OneFrameSize;     //1�R�}�ӂ�̃T�C�Y
	Vector2 CutStartPostion;  //�؂���J�n���W

	bool    Loop;//���[�v�����邩
}s_SpriteAnimation;

//=============================================================================
// �N���X��`
//=============================================================================
class Renderer_Polygon : public Singleton<Renderer_Polygon>
{
private:
	
	friend class Singleton<Renderer_Polygon>;//�V���O���g��

	//��`���_�o�b�t�@�[
	ID3D11Buffer* m_CubePolygonVertexBuffer;

	//�����_�o�b�t�@�[
	ID3D11Buffer* m_LineVertexBuffer;

	//3D�L���[�u���_�o�b�t�@�[
	ID3D11Buffer* m_VertexBuffer3DBox;
	
	//���_�����f�t�H���g�ɐݒ�
	void SetRectVertexToDefault(VERTEX_3D* _vertex);

	//3D���_�����f�t�H���g�ɐݒ�
	void Set3DBoxVertexToDefault(VERTEX_3D* _vertex, Vector3 _magni = Vector3(1.0f,1.0f,1.0f));

	//���n�e�N�X�`���[
	ID3D11ShaderResourceView* m_TextureWhite;

	//���C���E�B���h�E�L���b�V��
	class MainWindow* m_MainWindow = nullptr;

	//DX11�`��N���X�L���b�V��
	class Renderer_DirectX11* m_Renderer_DX11 = nullptr;

public:

	//�������E�I��
	 void Init();
	 void Uninit();

	 //���n�e�N�X�`���ݒ�
	 void SetDefaultTexture();

	 //���n�e�N�X�`���擾
	 inline ID3D11ShaderResourceView* GetDefaultTexture() { return m_TextureWhite; }
	

//=============================================================================
//
//  2D�`��n
//
//=============================================================================

	//�e�N�X�`���Ȃ�2D��`�`��
	 void DrawBox2D(Vector2 _postion, Vector2 _scale,
		 Color _color, bool _reverse = false, float _z = 0.0f);

	 //2D�X�v���C�g�`��
	 void Draw2D(Vector2 _postion, Vector2 _scale, Color _color,
		 bool _reverse = false,float _z = 0.0f);//�f�t�H���g�����͔��]�t���O��z���W

	 //2D�X�v���C�g�A�j���[�V�����`��
	 void Draw2DAnimation(Vector2 _position, Vector2 _scale, Color _color,
		 Vector2 _OneFrameSize, Vector2 _CutStartPostion,
		 bool _reverse = false);//�Ō�̃f�t�H���g�����͔��]�t���O

	 //2D���C���`��	 ����ʍ��㒆�S
	 void DrawLine2D(Vector2 _startPos, Vector2 _endPos, Color _color);

//=============================================================================
//
//  3D�`��n
//
//=============================================================================

	 //�r���{�[�h�`��
	 void DrawBillboard(Vector3 _postion, Vector3 _scale, Color _color, 
		 Vector2 _OneFrameSize, Vector2 _CutStartPostion,bool _isUseDefaultTex = false);

	 //�{�b�N�X�`��
	 void DrawBox(Vector3 _postion, Vector3 _Rotation,
		 Vector3 _scale, Color _color, bool _isLoop = true);

	 //���`��
	 void DrawLine(Vector3 _start, Vector3 _end, Color _color);

};
