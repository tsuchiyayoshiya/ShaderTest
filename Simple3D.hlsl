//������������������������������������������������������������������������������
// �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D	g_texture : register(t0);	//�e�N�X�`���[
SamplerState	g_sampler : register(s0);	//�T���v���[

//������������������������������������������������������������������������������
// �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global
{
	float4x4	matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	matW;	//���[���h�s��
	float4	diffuseColor;		// �f�B�t���[�Y�J���[�i�}�e���A���̐F�j
	bool		isTexture;		// �e�N�X�`���\���Ă��邩�ǂ���
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//�ʒu
	float2 uv	: TEXCOORD;	//UV���W
	float4 color	: COLOR;	//�F�i���邳�j
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	VS_OUT outData;

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
	outData.pos = mul(pos, matWVP);
	outData.uv = uv;

	//�@������]
	normal = mul(normal, matW);

	float4 light = float4(-1, 0.5, -0.7, 0);
	light = normalize(light);
	outData.color = clamp(dot(normal, light), 0, 1);

	//�܂Ƃ߂ďo��
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
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
	float4 posw : POSITION0;    //���[���h���W�n�̍��W
	float4 norw : NORMAL0;      //���[���h���W�n�̖@��
};

cbuffer ConstantBuffer
{
	float4 eyePos;            //���_���W
	float4 pntlightPos;       //�_�������W
	float4 pntlightCol;       //�_�����̐F
	float4 materialSpecular;  //���̂̐F(r,g,b,����x�W��)
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
	