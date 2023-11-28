//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D	g_texture : register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー

//───────────────────────────────────────
// コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
	float4x4	matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	matW;	//ワールド行列
	float4	diffuseColor;		// ディフューズカラー（マテリアルの色）
	bool		isTexture;		// テクスチャ貼ってあるかどうか
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//位置
	float2 uv	: TEXCOORD;	//UV座標
	float4 color	: COLOR;	//色（明るさ）
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matWVP);
	outData.uv = uv;

	//法線を回転
	normal = mul(normal, matW);

	float4 light = float4(-1, 0.5, -0.7, 0);
	light = normalize(light);
	outData.color = clamp(dot(normal, light), 0, 1);

	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float4 lightSource = float4(1.0f, 1.0f, 1.0f, 1.0f);
	//return lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;//float4(1,1,1,1)
	float4 diffuse;
	float4 ambient;

	if (isTexture == true) {
		diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
		ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * float4(0.3, 0.3, 0.3, 1);
	}
	else {
		diffuse = lightSource * diffuseColor * inData.color;
		ambient = lightSource * diffuseColor * float4(0.3, 0.3, 0.3, 1);
	}
	
	
	
	return diffuse + ambient;
}

struct PS_IN
{
	float4 pos  : SV_POSITION;
	float4 posw : POSITION0;    //ワールド座標系の座標
	float4 norw : NORMAL0;      //ワールド座標系の法線
};

cbuffer ConstantBuffer
{
	float4 eyePos;            //視点座標
	float4 pntlightPos;       //点光源座標
	float4 pntlightCol;       //点光源の色
	float4 materialSpecular;  //物体の色(r,g,b,光沢度係数)
}

float4 ps_main(PS_IN input) : SV_Target
{
	float3 l;
	float3 n;
	float3 r;
	float3 v;
	float  i;

	l = normalize(pntlightPos.xyz - input.posw.xyz);
	n = normalize(input.norw.xyz);
	r = 2.0 * n * dot(n, l) - l;
	v = normalize(eyePos.xyz - input.posw.xyz);
	i = pow(saturate(dot(r, v)), materialSpecular.w);

	return float4(i * materialSpecular.xyz * pntlightCol.xyz, 1.0);
}
	