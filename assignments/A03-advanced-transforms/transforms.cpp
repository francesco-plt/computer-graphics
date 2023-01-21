

// Rotate 45 degrees around an arbitrary axis passing through (1,0,-1). The x-axis can be aligned to the arbitrary axis after a
// rotation of 30 degrees around the z-axis, and then -60 degrees around the y-axis.
glm::mat4 MT1_T = glm::translate(glm::mat4(1), glm::vec3(1.0f, 0.0f, -1.0f));
glm::mat4 MT1_Ry = glm::rotate(glm::mat4(1), glm::radians(-60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
glm::mat4 MT1_Rz = glm::rotate(glm::mat4(1), glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
glm::mat4 MT1_Rx = glm::rotate(glm::mat4(1), glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
// undoing everything in reverse order to keep the rotation around the arbitrary axis
glm::mat4 MT1 = MT1_T * MT1_Ry * MT1_Rz * MT1_Rx * glm::inverse(MT1_Rz) * glm::inverse(MT1_Ry) * glm::inverse(MT1_T);

// Half the size of an object, using as fixed point (5,0,-2)
glm::mat4 MT2_T = glm::translate(glm::mat4(1), glm::vec3(5.0f, 0.0f, -2.0f));
glm::mat4 MT2_S = glm::scale(glm::mat4(1), glm::vec3(0.5f, 0.5f, 0.5f));
glm::mat4 MT2 = MT2_T * MT2_S * glm::inverse(MT2_T);

// Mirror the starship along a plane passing through (1,1,1), and obtained rotating 15 degree around the x axis the xz plane
glm::mat4 MT3_T = glm::translate(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f));
glm::mat4 MT3_Rx = glm::rotate(glm::mat4(1), glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
glm::mat4 MT3_S = glm::scale(glm::mat4(1), glm::vec3(1.0f, -1.0f, 1.0f)); // mirror along the xz plane (scale with axis not on plane negated)
glm::mat4 MT3 = MT3_T * MT3_Rx * MT3_S * glm::inverse(MT3_Rx) * glm::inverse(MT3_T);

// Apply the inverse of the following sequence of transforms: Translation of (0, 0, 5)
// then rotation of 30 degree around the Y axis, and finally a uniform scaling of a factor of 3.
glm::mat4 MT4_T = glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, 5.0f));
glm::mat4 MT4_Ry = glm::rotate(glm::mat4(1), glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
glm::mat4 MT4_S = glm::scale(glm::mat4(1), glm::vec3(3.0f, 3.0f, 3.0f));
glm::mat4 MT4 = glm::inverse(MT4_T) * glm::inverse(MT4_Ry) * glm::inverse(MT4_S);