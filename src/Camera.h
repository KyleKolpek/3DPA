#ifndef CAMERA_H
#define CAMERA_H

#include "GLM/glm.hpp"

/*************************************************************************//**
 * The camera for the game
 * Controls the view of the 3D assets (Actors, dungeon rooms, and other objects
 *****************************************************************************/

class Camera
{
public:
    
    /**********************************************************************//**
     * Default Camera constructor
     * not used
     *************************************************************************/
    Camera();
    
    /**********************************************************************//**
     * Camera constructor
     * \param[in] &eye
     *     The location of the camera in relation to the origin
     * \param[in] &at
     *     The focus of the camera, or where the camera is looking
     * \param[in] &up
     *     Contains a vector which points and declares an 'up'
     *************************************************************************/
    Camera(glm::vec3 const &eye,
           glm::vec3 const &at,
           glm::vec3 const &up);
    
    /**********************************************************************//**
     * Get the view matrix
     * Returns the view matrix of the camera
     *************************************************************************/
    glm::mat4 getViewMatrix() const;

    /**********************************************************************//**
     * Get the projection matrix
     * Returns the projection matrix of the camera
     *************************************************************************/
    glm::mat4 getProjectionMatrix() const;
    
    // These set the 3 vectors

    /**********************************************************************//**
     * set 'at' location
     * Changes the focus of the location to the given vector and changes
     * the view matrix
     * \param[in] &at
     *     Vector holding location of the focus of the camera
     *************************************************************************/
    void setAt(glm::vec3 const &at);

    /**********************************************************************//**
     * set 'eye' location
     * Changes the location of the eye of the camera and updates the view
     * matrix
     * \param[in] &eye
     *     Vector holding the new location for the eye of the camera
     *************************************************************************/
    void setEye(glm::vec3 const &eye);

    /**********************************************************************//**
     * set 'up' location
     * \param[in] &up
     *     Vector holding the new up vector
     *************************************************************************/
    void setUp(glm::vec3 const &up);

    // These modify the 3 vectors

    /**********************************************************************//**
     * Move the camera target
     * Moves the target of the camera based on the values of &at
     * \param[in] &at
     *     Vector holding the change in the at vector
     *************************************************************************/
    void moveAt(glm::vec3 const &at);
    
    /**********************************************************************//**
     * Move the camera eye
     * \param[in] &eye
     *     Holds the values to add to eye
     *************************************************************************/
    void moveEye(glm::vec3 const &eye);
    
    /**********************************************************************//**
     * Move the up vector
     * \param[in] &up
     *     Holds the values to add to up
     *************************************************************************/
    void moveUp(glm::vec3 const &up);
    
    // Getters

    /**********************************************************************//**
     * Get the at vector
     * Returns the location the camera is looking at as glm::vec3
     *************************************************************************/
    glm::vec3 getAt() const;

    /**********************************************************************//**
     * Get the eye vector
     * Returns the location of the eye of the camera as glm::vec3
     *************************************************************************/
    glm::vec3 getEye() const;
    
    /**********************************************************************//**
     * Get the up vector
     * Returns the location of the up vector as glm::vec3
     *************************************************************************/
    glm::vec3 getUp() const;

    /**********************************************************************//**
     * Generate and set the projection matrix
     * \param[in] fov
     *     Field of view
     * \param[in] aspect
     *     Aspect Ratio
     * \param[in] zNear
     *     Near clipping plane
     * \param[in] zFar
     *     Far clipping plane
     *************************************************************************/
    void perspective(float fov, float aspect, float zNear, float zFar);

protected:
    glm::vec3 eye;          /** Where the camera looks from            */
    glm::vec3 at;           /** Where the camera is looking at         */
    glm::vec3 up;           /** A vector pointing up                   */
    glm::mat4 viewMatrix;   /** the view matrix for the camera         */
    glm::mat4 projMatrix;   /** the projection matrix for the camera   */
    static float camSpeed;  /** The number of units to move the camera */
};

#endif
