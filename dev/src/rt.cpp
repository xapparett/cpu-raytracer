#include "rt.h"

// dont ask me why i put this here
namespace
{
    // https://www.youtube.com/watch?v=Qz0KTGYJtUk&t=1205s
    vec3 get_sky(const Ray &ray)
    {
        double gradientT { std::pow(GraphicsUtils::smoothstep(0.0, 0.4, ray.direction.y), 0.35) };
        vec3 gradient { lerpv(GraphicsUtils::SKY_COLOR_HORIZON, GraphicsUtils::SKY_COLOR_ZENITH, gradientT) };
    
        double groundToSky { GraphicsUtils::smoothstep(-0.01, 0.0, ray.direction.y) };
        return lerpv(GraphicsUtils::GROUND_COLOR, gradient, groundToSky);
    }
}

RT::RT(int W, int H):
    m_Width { W }, m_Height { H } {}

RT::~RT()
{
    delete[] m_Image;
}

vec3 RT::color(const Ray &ray, const vec3 &cameraPos, const vec3 &lightPos, int depth)
{
    vec3 final { 0.0 };

    if (depth >= 4)
        return get_sky(ray);

    Hit record;
    if (world.hit(ray, Interval { 0.0, CommonUtils::inf }, record))
    {
        vec3 ambient { 0.1 };
        vec3 sunColor { 1.0 };
        
        vec3 norm { unit(record.normal) };
        vec3 lightDir { lightPos - record.position };

        double diff { std::max(dot(norm, lightDir), 0.0) };
        vec3 diffuse { sunColor * diff };

        vec3 viewDir { unit(cameraPos - record.position) };
        vec3 reflDir { reflect(-lightDir, norm) };

        double spec { std::pow(std::max(dot(viewDir, reflDir), 0.0), record.material.shininess) };
        double specVal { record.material.specularStrength * spec };
        vec3 specular { specVal };
        
        // shadows
        double lightDist { (lightPos - record.position).length() };
        bool inShadow { false };

        vec3 shadowOrigin { record.position + (norm * CommonUtils::epsilon) };
        Ray shadowRay { shadowOrigin, lightDir };

        Hit shadowHit;

        if (world.hit(shadowRay, Interval { 0.0, CommonUtils::inf }, shadowHit))
            inShadow = true;

        double shadowMultiplier { inShadow ? 0.35 : 1.0 };
        final = ((diffuse + ambient + (specular * sunColor)) * record.material.color) * shadowMultiplier;

        if (record.material.is_reflective)
        {
            vec3 reflectedDir { reflect(ray.direction, norm) };
            vec3 reflectedOrigin { record.position + (norm * CommonUtils::epsilon) };

            vec3 reflectedColor { color({reflectedOrigin, reflectedDir}, cameraPos, lightPos, depth + 1) };
            final = reflectedColor * record.material.color;
        }

        return final;
    }
    
    return get_sky(ray);
}

void RT::init()
{
    m_Image = new uint8_t[ m_Width * m_Height * 4 ];
}

void RT::render()
{
    Camera camera { { 0.0, 0.0, 0.0 }, 1.0 };
    camera.init(m_Width, m_Height);

    world.add(std::make_shared<Sphere>(0.5, vec3 { 0.0, 0.0, -1.0 }, Material { 0.1, 8.0, false, vec3 { 1.0, 0.3, 0.3 } }));        // red ball
    world.add(std::make_shared<Sphere>(0.1, vec3 { 0.0, 0.59, -1.0 }, Material { 0.1, 8.0, false, vec3 { 1.0, 1.0, 0.6 } }));       // tiny ball
    world.add(std::make_shared<Sphere>(100., vec3 { 0.0, -100.5, -1.0 }, Material { 0.1, 16.0, false, vec3 { 0.1, 1.0, 0.0 } }));   // big ball
    world.add(std::make_shared<Sphere>(0.75, vec3 { -1.5, 0.7, -2.0 }, Material { 0.0, 0.0, true, vec3 { 0.7, 0.7, 1.0 } }));       // reflective ball
    world.add(std::make_shared<Sphere>(0.35, vec3 { 0.75, 0.5, -1.1 }, Material { 0.0, 0.0, true, vec3 { 0.5, 0.8, 0.2 } }));       // another reflective ball
    world.add(std::make_shared<Sphere>(0.2, vec3 { 0.25, -0.5, -0.6 }, Material { 0.0, 0.0, true, vec3 { 0.0, 1.0, 1.0 } }));       // aandd another one

    vec3 lightPosition { -1.0, 1.0, -0.1 };

    for (int y = 0; y < m_Height; y++)
    {
        for (int x = 0; x < m_Width; x++)
        {
            const int offset { (y * m_Width + x) * 4 };

            vec3 pixel_coord { camera.pixel_loc + (camera.pixel_u * x) + (camera.pixel_v * y) };
            vec3 ray_dir { pixel_coord - camera.position };

            Ray ray { camera.position, ray_dir };
            vec3 final { color(ray, camera.position, lightPosition) };

            m_Image[offset + 0] = std::clamp(255 * static_cast<float>(final.x), 0.f, 255.f);
            m_Image[offset + 1] = std::clamp(255 * static_cast<float>(final.y), 0.f, 255.f);
            m_Image[offset + 2] = std::clamp(255 * static_cast<float>(final.z), 0.f, 255.f);
            m_Image[offset + 3] = 255;
        }
    }

    std::time_t t { std::time(nullptr) };
    std::tm *now { std::localtime(&t) };

    std::ostringstream oss;
    oss << std::put_time(now, "%m%d%Y_%H%M%S");

    std::string filename { RTOUT + std::format("{}.png", oss.str()) };
    stbi_write_png(filename.c_str(), m_Width, m_Height, 4, m_Image, m_Width * 4);
}