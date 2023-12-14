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
	float4x4	matNormal;
	float4		diffuseColor;		// �f�B�t���[�Y�J���[�i�}�e���A���̐F�j
	float4      ambientColor;
	float4		lightPosition;
	float4		eyePosition;
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
	float4 eyev		:POSITION;
	float4 normal	:NORMAL;
};

/*struct PS_IN
{
	float4 pos    : SV_POSITION;	//�ʒu
	float2 uv	: TEXCOORD;	//UV���W
	float4 eyev		:POSITION1;
	float4 normal	:POSITION2;
	float4 light	:POSITION3;
};*/

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	VS_OUT outData = (VS_OUT)0;

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
	outData.pos = mul(pos, matWVP);
	//outData.uv = uv;
	outData.uv = uv;
	normal.w = 0;
	normal = mul(normal, matNormal);
	normal = normalize(normal);
	outData.normal = normal;

	float4 light = normalize(lightPosition);
	//light = normalize(light);

	outData.color = saturate(dot(normal, light));
	float4 posw = mul(pos, matW);
	outData.eyev = eyePosition - posw;



	//�@������]
	/*normal = mul(normal, matW);

	float4 light = float4(1, 0, 0, 0);
	light = normalize(light);
	outData.color = clamp(dot(normal, light), 0, 1);*/

	//�܂Ƃ߂ďo��
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
	/*float4 light = float4(0.0, 2, 0, 1);//�_�����̈ʒu
	light = mul(light, matW);
	float3 LD = inData.pos_ - light;//���̕����x�N�g��
	float len = length(LD);//���̕����x�N�g���𐳋K��
	float4 outColor = { 1, 1, 1, 1 };
	float lightMagnitude = seturate(dot(inData.normal, -normalize(LD)));
	float k = seturate(1.0f / (1.0f + 1.0 * len * len));

	return outColor * (0.8 * k * lightMagnitude * 0.2f);*/

	float4 lightSource = float4(1.0f, 1.0f, 1.0f, 1.0f);
	//float4 ambentSource = float4(0.2f, 0.2f, 0.2f, 1.0f);//��
	float4 ambientSource = ambientColor;
	//return lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;//float4(1,1,1,1)
	float4 diffuse;
	float4 ambient;
	float4 NL = dot(inData.normal,normalize(lightPosition));
	float4 reflect = normalize(2 * NL * inData.normal - normalize(lightPosition));
	//float4 reflect = reflect;
	float4 specular = pow(saturate(dot(reflect,normalize(inData.eyev))),8);
	if (isTexture == false) {
		diffuse = lightSource * diffuseColor * inData.color;
		ambient = lightSource * diffuseColor * ambientSource;
	}
	else {
		diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
		ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambientSource;
	}
	return diffuse + ambient + specular;
}