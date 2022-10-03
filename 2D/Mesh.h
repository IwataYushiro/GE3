#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <dinput.h>
#include <DirectXMath.h>
#include <wrl.h>

using namespace DirectX;

//定数バッファ用データ構造体(マテリアル)
struct ConstBufferDataMaterial
{
	XMFLOAT4 color;	//色(RGBA)

};
struct ConstBufferDataTransform
{
	XMMATRIX mat; // 3D変換行列

};
class Mesh
{
public: // メンバ関数
	Mesh();
	~Mesh();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(HRESULT result, ID3D12Device* device);

	template<typename T1, typename T2>
	void CreateConstBuffer(T1* cb, ID3D12Device* device, ID3D12Resource*& buffer, T2*& cbm);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(BYTE* keys);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* commandList);

private://メンバ変数

	//ウィンドゥサイズ
	const int windowWidth = 1280; //横幅
	const int windowHeight = 720; //縦幅

	struct Vertex
	{
		XMFLOAT3 pos;		//xyz座標
		XMFLOAT2 uv;		//uv座標
	};

	//頂点データ
	Vertex vertices_[4] = {
		// x	 y	  z		 u	  v
		{{-50.0f ,-50.0f ,0.0f},{0.0f,1.0f}},//左下	Xが-で左　Yが-で下
		{{-50.0f,  50.0f ,0.0f},{0.0f,0.0f}},//左上	Xが+で右　Yが+で上
		{{ 50.0f ,-50.0f ,0.0f},{1.0f,1.0f}},//右下					
		{{ 50.0f , 50.0f ,0.0f},{1.0f,0.0f}},//右上					
	};

	//インデックスデータ
	unsigned short indices[6] =
	{
		0,1,2,//三角形1つ目
		1,2,3,//三角形2つ目
	};

	//定数バッファのGPUリソースのポインタ
	ID3D12Resource* constBuffMaterial = nullptr;
	ID3D12Resource* constBuffTransform = nullptr;

	//構造体を変数化
	ConstBufferDataMaterial* cbdm = nullptr;
	ConstBufferDataTransform* cbdt = nullptr;

	//マッピング用のポインタ
	ConstBufferDataMaterial* constMapMaterial = nullptr;
	ConstBufferDataTransform* constMapTransform = nullptr;

	//射影変換行列
	XMMATRIX matprojection;

	//ビュー変換行列
	XMMATRIX matview;
	//視点
	XMFLOAT3 eye;
	//注視点
	XMFLOAT3 target;
	//上方向ベクトル
	XMFLOAT3 up;
	
	//ワールド変換行列
	XMMATRIX matWorld;
	//スケーリング行列
	XMMATRIX matScale;
	//スケーリング倍率
	XMFLOAT3 scale;
	 
	//回転行列
	XMMATRIX matRot;
	//回転角
	XMFLOAT3 rotation;
	
	//平行移動行列
	XMMATRIX matTrans;
	//座標
	XMFLOAT3 position;

	//頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vdView{};

	//インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW idView{};

	//設定をもとにSRV用デスクリプタヒープを生成
	ID3D12DescriptorHeap* srvHeap = nullptr;

	//GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得
	Vertex* vertMap = nullptr;

	//ルートシグネチャ
	ID3D12RootSignature* rootSignature;

	//パイプラインステートの生成
	ID3D12PipelineState* pipelineState = nullptr;



	float angle = 0.0f;//カメラの回転角
};
