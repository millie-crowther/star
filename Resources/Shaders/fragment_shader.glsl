uniform vec2 window_size;

float f = 1.0;
float render_distance = 1000.0;

bool hit(float d){
    return d < render_distance;
}

float d(vec3 r){
    vec3 centre = vec3(0.0, 0.0, 3.0);
    float radius = 0.5;
    
    vec3 x = vec3(0.0);
    while (abs(length(centre - x) - radius) > 0.0001 && hit(length(x))){
        float distance = length(centre - x) - radius;
        x += r * distance * 0.5;
    }

    return length(x);
}

vec3 get_ray(vec2 uv){
    return normalize(vec3(uv, f));
}

vec4 sky(vec3 dir){
    return vec4((dir.xy + 1.0) / 2.0, 1.0, 1.0);
}

void main(){
    vec2 uv = gl_FragCoord.xy / window_size;
    uv = uv * 2.0 - 1.0;
    uv.x *= window_size.x / window_size.y;
    vec2 pos = uv;
    
    vec3 r = get_ray(pos);
    float depth = d(r);
    
    if (hit(depth)){
        gl_FragColor = vec4(vec3(depth * depth) / 200.0, 1.0);
    } else {
        gl_FragColor = sky(r); 
    }
}

