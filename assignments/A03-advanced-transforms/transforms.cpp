

// Rotate 45 degrees around an arbitrary axis passing through (1,0,-1). The x-axis can be aligned to the arbitrary axis after a
// rotation of 30 degrees around the z-axis, and then -60 degrees around the y-axis.
glm::mat4 MT1arbAxisTranslation = glm::translate(glm::mat4(1), glm::vec3(1.0f, 0.0f, -1.0f));
glm::mat4 MT1minus60yAxisRotation = glm::rotate(glm::mat4(1), glm::radians(-60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
glm::mat4 MT130zAxisRotation = glm::rotate(glm::mat4(1), glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
glm::mat4 MT1arbAxisRotation = glm::rotate(glm::mat4(1), glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
// undoing everything in reverse order to keep the rotation around the arbitrary axis
glm::mat4 MT1 =
    MT1arbAxisTranslation *
    MT1minus60yAxisRotation *
    MT130zAxisRotation *
    MT1arbAxisRotation * // this is the actual rotation around the arbitrary axis which we'll not undo with the inverse() function
    glm::inverse(MT130zAxisRotation) *
    glm::inverse(MT1minus60yAxisRotation) *
    glm::inverse(MT1arbAxisTranslation);

// Half the size of an object, using as fixed point (5,0,-2)
glm::mat4 MT2fixedPointTranslation = glm::translate(glm::mat4(1), glm::vec3(5.0f, 0.0f, -2.0f));
glm::mat4 MT2Scaling = glm::scale(glm::mat4(1), glm::vec3(0.5f, 0.5f, 0.5f));
glm::mat4 MT2 =
    MT2fixedPointTranslation *
    MT2Scaling *
    glm::inverse(MT2fixedPointTranslation);

// Mirror the starship along a plane passing through (1,1,1), and obtained rotating 15 degree around the x axis the xz plane
glm::mat4 MT3fixedPointTranslation = glm::translate(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f));
glm::mat4 MT115xAxisRotation = glm::rotate(glm::mat4(1), glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
glm::mat4 MT3xzMirroring = glm::scale(glm::mat4(1), glm::vec3(1.0f, -1.0f, 1.0f)); // mirror along the xz plane (scale with axis not on plane negated)
glm::mat4 MT3 =
    MT3fixedPointTranslation *
    MT115xAxisRotation *
    MT3xzMirroring *
    glm::inverse(MT115xAxisRotation) *
    glm::inverse(MT3fixedPointTranslation);

// Apply the inverse of the following sequence of transforms: Translation of (0, 0, 5)
// then rotation of 30 degree around the Y axis, and finally a uniform scaling of a factor of 3.
glm::mat4 MT4fixedPointTranslation = glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, 5.0f));
glm::mat4 MT130yAxisRotation = glm::rotate(glm::mat4(1), glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
glm::mat4 MT4Scaling = glm::scale(glm::mat4(1), glm::vec3(3.0f, 3.0f, 3.0f));
glm::mat4 MT4 =
    glm::inverse(MT4fixedPointTranslation) *
    glm::inverse(MT130yAxisRotation) *
    glm::inverse(MT4Scaling);