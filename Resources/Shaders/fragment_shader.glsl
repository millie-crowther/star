#version 430

uniform vec2 window_size;
uniform vec3 camera_up;
uniform vec3 camera_right;
uniform vec3 camera_position;

float f = 1.0;
float render_distance = 1000.0;
int max_steps = 64;
float epsilon = 0.005;
float shadow_softness = 64;

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

float cube(vec3 p, vec3 s){
    vec3 d = abs(p) - s / 2;
    return min(max(d.x, max(d.y,d.z)), 0.0) + length(max(d,0.0));
}

float sphere(vec3 p, float r, vec3 c){
    return length(p - c) - r;
}

float plane(vec3 p, vec3 n){
    return dot(p, n);
}

float stool(vec3 p){
    p = vec3(abs(p.x), p.y, abs(p.z));
    float legs = cube(p - vec3(0.2, 0.25, 0.2), vec3(0.07, 0.5, 0.07)); 
    float seat = cube(p - vec3(0, 0.5, 0), vec3(0.52, 0.08, 0.52));
    return min(legs, seat) - 0.01;
}

// signed distance function
float phi(vec3 p){
    //TODO: this is the big boy
    float plane = plane(p, vec3(0, 1, 0));
    float d = stool(p - vec3(0, 0, 3));
    return min(d, plane);
}

vec3 normal(vec3 p){
    vec3 dx = vec3(epsilon, 0, 0); 
    vec3 dy = vec3(0, epsilon, 0); 
    vec3 dz = vec3(0, 0, epsilon);

    return normalize(vec3(
        phi(p + dx) - phi(p - dx),
	phi(p + dy) - phi(p - dy),
	phi(p + dz) - phi(p - dz)
    ));
}

ray advance(ray r){
    //TODO: space warping goes here
    float dist = phi(r.pos);
    r.pos += r.dir * dist;
    r.hit = dist <= epsilon;
    r.dist += dist;
    return r;
}

ray raycast(ray r){
    for (int i = 0; i < max_steps && !r.hit && r.dist < render_distance; i++){
	r = advance(r);
    }
    return r;
}

float shadow(vec3 l, vec3 p){
    ray r = raycast(ray(l, normalize(p - l), 0, false));
    if (length(r.pos - p) > epsilon * 2){
        return 0.0;
    } else {
        return 1.0;
    }
}

ray get_ray(vec2 uv){
    vec3 camera_forward = cross(camera_right, camera_up);

    vec3 dir = camera_forward * f;
    dir += camera_up * uv.y;
    dir += camera_right * uv.x;
    dir = normalize(dir);
   
    return ray(camera_position, dir, 0, false);
}

vec4 colour(vec3 p){
    if (p.y <= epsilon){
	return vec4(0.5, 0.7, 0.9, 1.0);
    } else {
        return vec4(0.8, 0.5, 0.8, 1.0);
    }
}

vec4 light(vec3 p){
    //TODO: 1) blinn-phong lighting
    //      2) more complex lighting
    vec3 pos = vec3(1);
    vec4 colour = vec4(5);
    float kd = 0.5;
    float ks = 0.5;
    float shininess = 32;

    // attenuation
    float dist = length(pos - p);
    float attenuation = 1.0 / (dist * dist);

    //ambient 
    vec4 a = vec4(0.5, 0.5, 0.5, 1.0);

    //shadows
    ray ry = ray(pos, normalize(p - pos), 0, false);
    ry = raycast(ry);
    float shadow = shadow(pos, p);

    //diffuse
    vec3 l = normalize(pos - p);
    vec3 n = normal(p);
    vec4 d = kd * dot(l, n) * colour;

    //specular
    vec3 v = normalize(p);
    vec3 r = reflect(l, n);
    vec4 s = ks * pow(max(dot(r, v), epsilon), shininess) * colour;
    return a + (d + s) * attenuation * shadow;
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

