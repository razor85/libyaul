#include <gamemath/fix16/fix16_vec3.h>
#include <gamemath/fix16/fix16_quat.h>

#if defined(__cplusplus)

namespace yaul {

const fix16_vec3 fix16_vec3::operator*(const fix16_quat &other) const
{
    fix16_vec3_t result;
    fix16_quat_vec3_mul(other.as_fix16_quat_t(), as_fix16_vec3_t(), &result);

    return fix16_vec3 { result.x, result.y, result.z };
}

} // namespace yaul

#endif /* __cplusplus */
