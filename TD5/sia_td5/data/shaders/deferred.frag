#version 410 core

uniform vec4 light_pos0;
uniform vec3 light_col0;
uniform vec4 light_pos1;
uniform vec3 light_col1;
uniform vec4 light_pos2;
uniform vec3 light_col2;

uniform mat4 inv_projection_matrix;
uniform vec2 window_size;

uniform sampler2D rendered_texture;
uniform sampler2D normal_texture;
uniform sampler2D depth_texture;

in vec4 gl_FragCoord;

out vec4 out_color;


// Tel que fourni dans l'enonce
vec3 VSPositionFromDepth(vec2 texcoord, float z)
{
    // Get x/w and y/w from the viewport position
    vec4 positionNDC = vec4(2 * vec3(texcoord, z) - 1, 1.f);
    // Transform by the inverse projection matrix
    vec4 positionVS = inv_projection_matrix * positionNDC;
    // Divide by w to get the view-space position
    return positionVS.xyz / positionVS.w;
}

// Tel que fourni dans blinn.frag
vec3 shade(vec3 N, vec3 L, vec3 V,
           vec3 color, float Ka, float Kd, float Ks,
           vec3 lightCol, float shininess){

    vec3 final_color = color * Ka * lightCol;	//ambient

    float lambertTerm = dot(N,L);		//lambert

    if(lambertTerm > 0.0) {
        final_color += color * Kd * lambertTerm * lightCol; 	//diffuse

        vec3 R = reflect(-L,N);
        float specular = pow(max(dot(R,V), 0.0), shininess);
        final_color +=  Ks * lightCol * specular;	//specular
    }

    return final_color;
}

void main()
{
    vec2 texCoords = gl_FragCoord.xy / window_size;

    vec4 vert_color = texture(rendered_texture, texCoords);
    vec3 vert_normal = texture(normal_texture, texCoords).rgb;
    float vert_depth = texture(depth_texture, texCoords).x;

		vec3 vert_pos_view = VSPositionFromDepth(texCoords, vert_depth);


		// LIGHT 1
		vec3 l = vec3(light_pos0.rgb - vert_pos_view);

    out_color.rgb = shade(normalize(vert_normal), normalize(l), -normalize(vert_pos_view.xyz),
                          vert_color.rgb, 0.2, 0.7, vert_color.a, light_col0/max(1,dot(l,l)*0.05), 5);

		// LIGHT 2
		l = vec3(light_pos1.rgb - vert_pos_view);

    out_color.rgb += shade(normalize(vert_normal), normalize(l), -normalize(vert_pos_view.xyz),
                          vert_color.rgb, 0.2, 0.7, vert_color.a, light_col1/max(1,dot(l,l)*0.05), 5);

		// LIGHT 3
		l = vec3(light_pos2.rgb - vert_pos_view);

    out_color.rgb += shade(normalize(vert_normal), normalize(l), -normalize(vert_pos_view.xyz),
                          vert_color.rgb, 0.2, 0.7, vert_color.a, light_col2/max(1,dot(l,l)*0.05), 5);

    out_color.a = 1.0;

  	//out_color = vert_color;
    //out_color = vec4(vert_normal, 1.0);
    //out_color = vec4(vec3(vert_depth), 1.0);
}
