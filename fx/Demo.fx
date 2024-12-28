

struct VSOutput
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
};



VSOutput VS_Main(
				  float4 pos : POSITION,    //Vertex Position
				  float4 color : COLOR0 //Vertex Color	: "Diffuse"	
				)
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




float4 PS_Main(
				float4 pos : SV_POSITION, 
				float4 color : COLOR0       
				) : SV_TARGET
{
	//float4 col = {1, 0, 1, 1};

    return color;
}

