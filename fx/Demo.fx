

struct VSOutput
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
    uint viewportIndex : SV_ViewportArrayIndex;
};

float4 cbColor : register(b0);

VSOutput VS_Main( float4 pos : POSITION,  float4 color : COLOR0 )
{

	VSOutput output = (VSOutput)0;

	//정점 좌표를 클립스페이스(Clip Space)로 전환 (해상도 960x600 기준)
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


float4 PS_Main(VSOutput input) : SV_TARGET
{
    if (input.viewportIndex == 0)
    {
        return input.col;
    }
    else if (input.viewportIndex == 1)
    {
        return cbColor;
    }
    else if (input.viewportIndex == 2)
    {
        return input.col + input.col * cbColor;
    }
    return input.col;
}

