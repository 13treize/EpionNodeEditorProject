cbuffer CONSTANT_BUFFER : register(b0)
{
    row_major float4x4 world_view_projection;
    row_major float4x4 world;
    float4 material_color;
    float4 light_direction;
    //float  noise;
};
