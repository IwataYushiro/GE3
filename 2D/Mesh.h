#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <dinput.h>
#include <DirectXMath.h>
#include <wrl.h>

using namespace DirectX;

//�萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
struct ConstBufferDataMaterial
{
	XMFLOAT4 color;	//�F(RGBA)

};
struct ConstBufferDataTransform
{
	XMMATRIX mat; // 3D�ϊ��s��

};
class Mesh
{
public: // �����o�֐�
	Mesh();
	~Mesh();
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(HRESULT result, ID3D12Device* device);

	template<typename T1, typename T2>
	void CreateConstBuffer(T1* cb, ID3D12Device* device, ID3D12Resource*& buffer, T2*& cbm);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update(BYTE* keys);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* commandList);

private://�����o�ϐ�

	//�E�B���h�D�T�C�Y
	const int windowWidth = 1280; //����
	const int windowHeight = 720; //�c��

	struct Vertex
	{
		XMFLOAT3 pos;		//xyz���W
		XMFLOAT2 uv;		//uv���W
	};

	//���_�f�[�^
	Vertex vertices_[4] = {
		// x	 y	  z		 u	  v
		{{-50.0f ,-50.0f ,0.0f},{0.0f,1.0f}},//����	X��-�ō��@Y��-�ŉ�
		{{-50.0f,  50.0f ,0.0f},{0.0f,0.0f}},//����	X��+�ŉE�@Y��+�ŏ�
		{{ 50.0f ,-50.0f ,0.0f},{1.0f,1.0f}},//�E��					
		{{ 50.0f , 50.0f ,0.0f},{1.0f,0.0f}},//�E��					
	};

	//�C���f�b�N�X�f�[�^
	unsigned short indices[6] =
	{
		0,1,2,//�O�p�`1��
		1,2,3,//�O�p�`2��
	};

	//�萔�o�b�t�@��GPU���\�[�X�̃|�C���^
	ID3D12Resource* constBuffMaterial = nullptr;
	ID3D12Resource* constBuffTransform = nullptr;

	//�\���̂�ϐ���
	ConstBufferDataMaterial* cbdm = nullptr;
	ConstBufferDataTransform* cbdt = nullptr;

	//�}�b�s���O�p�̃|�C���^
	ConstBufferDataMaterial* constMapMaterial = nullptr;
	ConstBufferDataTransform* constMapTransform = nullptr;

	//�ˉe�ϊ��s��
	XMMATRIX matprojection;

	//�r���[�ϊ��s��
	XMMATRIX matview;
	//���_
	XMFLOAT3 eye;
	//�����_
	XMFLOAT3 target;
	//������x�N�g��
	XMFLOAT3 up;
	
	//���[���h�ϊ��s��
	XMMATRIX matWorld;
	//�X�P�[�����O�s��
	XMMATRIX matScale;
	//�X�P�[�����O�{��
	XMFLOAT3 scale;
	 
	//��]�s��
	XMMATRIX matRot;
	//��]�p
	XMFLOAT3 rotation;
	
	//���s�ړ��s��
	XMMATRIX matTrans;
	//���W
	XMFLOAT3 position;

	//���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vdView{};

	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW idView{};

	//�ݒ�����Ƃ�SRV�p�f�X�N���v�^�q�[�v�𐶐�
	ID3D12DescriptorHeap* srvHeap = nullptr;

	//GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	Vertex* vertMap = nullptr;

	//���[�g�V�O�l�`��
	ID3D12RootSignature* rootSignature;

	//�p�C�v���C���X�e�[�g�̐���
	ID3D12PipelineState* pipelineState = nullptr;



	float angle = 0.0f;//�J�����̉�]�p
};
