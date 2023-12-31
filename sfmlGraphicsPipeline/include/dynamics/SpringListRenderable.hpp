#ifndef SPRING_LIST_RENDERABLE_HPP
#define SPRING_LIST_RENDERABLE_HPP

#include "../MeshRenderable.hpp"
#include "SpringForceField.hpp"
#include <list>
#include <vector>


/**@brief Render a collection of springs.
 *
 * Render a set of springs on screen. We could do much more here than just
 * rendering a line between the centers of the two spring's particles.
 * However, it is up to you to come with better idea :-).
 */
class SpringListRenderable : public MeshRenderable
{
public:
    ~SpringListRenderable();
    /**@brief Build a renderable to render a list of springs.
     *
     * Build a new renderable to render a list of springs.
     * @param program The shader program used to render the springs.
     * @param springForceFields The set of springs force fields that model
     * the springs we want to render.
     */
    SpringListRenderable( ShaderProgramPtr program, std::list<SpringForceFieldPtr>& springForceFields );

protected:
    void do_draw();

private:
    void update_spring_positions();

    std::list<SpringForceFieldPtr> m_springForceFields;
};

typedef std::shared_ptr<SpringListRenderable> SpringListRenderablePtr;

#endif // SPRING_LIST_RENDERABLE_HPP

