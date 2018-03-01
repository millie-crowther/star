#version 430

//layout(std430, binding = 0) buffer octree_buffer {
//    int octree_size;
//    int octree[];
//};

uniform vec2 window_size;
uniform vec3 camera_up;
uniform vec3 camera_right;
uniform vec3 camera_pos;

float f = 1.0;
float render_distance = 1000.0;
int max_steps = 64;
float epsilon = 0.05;

// data structure for a ray
struct ray {
    // position of the ray
    vec3 pos;

    // current direction of the ray
    vec3 dir;

    // distance: allows non-euclidean geometry
    float dist;

    // whether or not the ray has hit something
    bool hit;
};

//data structure for a point light
struct point_light {
    vec3 pos;
    vec4 colour;
};

float d(vec3 pos){
    //TODO: this is the big boy
    vec3 centre = vec3(0, 0.6, 3);
    float radius = 0.5;
    float sphere = length(pos - centre) - radius;
    float plane = dot(pos, vec3(0, 1, 0));
    return min(sphere, plane);
}

ray advance(ray r){
    //TODO: space warping goes here
    float dist = d(r.pos);
    r.dist += dist;
    r.pos += r.dir * dist;
    r.hit = dist <= epsilon;
    return r;
}

ray raycast(ray r){
    for (int i = 0; i < max_steps && !r.hit && r.dist < render_distance; i++){
	r = advance(r);
    }
    return r;
}

ray get_ray(vec2 uv){
    vec3 camera_forward = cross(camera_right, camera_up);

    vec3 dir = camera_forward * f;
    dir += camera_up * uv.y;
    dir += camera_right * uv.x;
    dir = normalize(dir);
   
    //TODO: change camera origin
    return ray(vec3(0, 0.5, 0), dir, 0, false);
}

vec4 colour(vec3 p){
    if (p.y <= epsilon){
	return vec4(0.5, 0.7, 0.9, 1.0);
    } else {
        return vec4(0.8, 0.5, 0.8, 1.0);
    }
}

vec4 ambient(vec3 p){
    return vec4(0.5, 0.5, 0.5, 1);
}

vec4 diffuse(vec3 p){
    return vec4(0);
}

vec4 specular(vec3 p){
    return vec4(0);
}

vec4 light(vec3 p){
    //TODO: 1) blinn-phong lighting
    //      2) more complex lighting
    return ambient(p) + diffuse(p) + specular(p);
}

vec4 sky(){
    //TODO: decide what to do with sky
    return vec4(0);
}

void main(){
    vec2 uv = gl_FragCoord.xy / window_size;
    uv = uv * 2.0 - 1.0;
    uv.x *= window_size.x / window_size.y;
    vec2 pos = uv;
    
    ray r = get_ray(pos);
    r = raycast(r);
    
    if (r.hit){
        gl_FragColor = colour(r.pos) * light(r.pos);
    } else {
        gl_FragColor = sky(); 
    }
}

