

struct VSOutput
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
    uint viewportIndex : SV_ViewportArrayIndex;
};



VSOutput VS_Main( float4 pos : POSITION,  float4 color : COLOR0 )
{

	VSOutput output = (VSOutput)0;

	//���� ��ǥ�� Ŭ�������̽�(Clip Space)�� ��ȯ (�ػ� 960x600 ����)
	//  0 ~ 800  -->  -1 ~ +1
	pos.x = (pos.x - 480) / 480;
	pos.y = (pos.y - 300) /-300;
	
	output.pos = pos;	
    output.col = color;

    return output;
}

[maxvertexcount(9)]
void GS_Main(triangle VSOutput input[3], inout TriangleStream<VSOutput> output)
{
    for (int v = 0; v < 3; ++v)
    {
        for (int i = 0; i < 3; ++i)
        {
            VSOutput vertex = input[i];
            vertex.viewportIndex = v;
            output.Append(vertex);
        }
    }
}


float4 PS_Main(VSOutput output) : SV_TARGET
{
	//float4 col = {1, 0, 1, 1};

    return output.col;
}

