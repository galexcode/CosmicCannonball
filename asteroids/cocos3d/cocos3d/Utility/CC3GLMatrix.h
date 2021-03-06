/*
 * CC3GLMatrix.h
 *
 * cocos3d 0.7.1
 * Author: Bill Hollings
 * Copyright (c) 2010-2012 The Brenwill Workshop Ltd. All rights reserved.
 * http://www.brenwill.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * http://en.wikipedia.org/wiki/MIT_License
 */

/** @file */	// Doxygen marker

#import "CC3MatrixMath.h"

/**
 * Enumeration of the options for the starting vector
 * when orthonormalizing the basis vectors of a matrix.
 */
typedef enum {
	kCC3GLMatrixOrthonormalizationStartX,	/**< Start with the X-axis basis vector. */
	kCC3GLMatrixOrthonormalizationStartY,	/**< Start with the Y-axis basis vector. */
	kCC3GLMatrixOrthonormalizationStartZ	/**< Start with the Z-axis basis vector. */
} CC3GLMatrixOrthonormalizationStart;

/**
 * A wrapper class for a 4x4 OpenGL matrix array.
 *
 * This matrix wrapper is implemented as a class cluster design pattern.
 * Different concrete implementation classes are provided to handle different underlying
 * matrix data storage requirements. You do not need to be aware of the concrete classes,
 * which aare selected and instantiated automatically by the class allocation methods.
 */
@interface CC3GLMatrix : NSObject <NSCopying> {
	BOOL isIdentity;
}

/**
 * Returns a pointer to the underlying array of 16 GLfloats stored in column-major order.
 * This can be passed directly into the standard OpenGL ES matrix functions.
 *
 * The effect of setting this property depends on how this instance was initialized.
 *
 * If this instance was initialized on an existing 4x4 GL matrix array using the
 * initOnGLMatrix: or matrixOnGLMatrix: methods, this matrix can be reassigned to
 * wrap a different underlying GL matrix array by setting the value of this property.
 *
 * If this instance was initialized with any other method, setting the value of
 * this property has no effect.
 */
@property(nonatomic, assign) GLfloat* glMatrix;

/** 
 * Indicates whether this matrix is an identity matrix.
 *
 * This can be useful for short-circuiting many otherwise consumptive calculations.
 * For example, this class is implemented so that, matrix multiplication is not
 * performed as a raw calculation if one of the matrices is an identity matrix.
 * In addition, transposition and inversion of an identity matrix are no-ops.
 *
 * This values is set to YES after the matrix is initialized or populated as an
 * identity matrix, or populated by an identity transform. It is set to NO whenever
 * an operation is performed on this matrix that no longer results in it being an
 * identity matrix.
 *
 * This flag is only set to YES if the matrix is deliberately populated as an
 * identity matrix. It will not be set to YES if an operation results in the
 * contents of this matrix matching those of an identity matrix by accident.
 */
@property(nonatomic, readonly) BOOL isIdentity;


#pragma mark Allocation and initialization

/** Returns an initialized instance with all elements set to zero. */
-(id) init;

/** Allocates and returns an initialized autoreleased instance with all elements set to zero. */
+(id) matrix;

/**
 * Returns an initialized instance with all elements populated as an identity matrix
 * (ones on the diagonal, zeros elsewhere).
 */
-(id) initIdentity;

/**
 * Allocates and returns an initialized autoreleased instance with all elements
 * populated as an identity matrix (ones on the diagonal, zeros elsewhere).
 */
+(id) identity;

/**
 * Returns an initialized instance with all elements copied from the specified
 * GL matrix, which must be a standard 4x4 OpenGL matrix in column-major order.
 */
-(id) initFromGLMatrix: (GLfloat*) aGLMtx;

/**
 * Allocates and returns an initialized autoreleased instance with all elements copied from
 * the specified GL matrix, which must be a standard 4x4 OpenGL matrix in column-major order.
 */
+(id) matrixFromGLMatrix: (GLfloat*) aGLMtx;

/**
 * Allocates and returns an initialized autoreleased instance that is the result of
 * multiplying the first matrix by the second (m1 x m2).
 *
 * Neither of the two input matrices is modified.
 */
+(id) matrixByMultiplying: (CC3GLMatrix*) m1 by: (CC3GLMatrix*) m2;

/**
 * Returns an initialized instance that wraps the specified GL matrix, which must be a
 * standard 4x4 OpenGL matrix in column-major order. Changes to this matrix instance will
 * change the underlying data passed here. This is useful when the matrix data was supplied
 * and loaded by some other mechanism, such as a file loader. Rather than copying the data
 * into a new matrix, resulting in two copies of the matrix data, a CC3GLMatrix instance
 * can be initialized to wrap the data.
 *
 * Once initialized, this matrix can be reassigned to wrap a different underlying GL matrix
 * array by setting the value of this property. In this way, a single instance of CC3GLMatrix
 * can be used to manipulate a number of GL matrices.
 *
 * This instance makes no attempt to manage the underlying GL matrix memory. It is up to
 * the application to manage this memory.
 */
-(id) initOnGLMatrix: (GLfloat*) aGLMtx;

/**
 * Allocates and returns an initialized autoreleased instance that wraps the specified GL matrix,
 * which must be a standard 4x4 OpenGL matrix in column-major order. Changes to this matrix
 * instance will change the underlying data passed here. This is useful when the matrix data was
 * supplied and loaded by some other mechanism, such as a file loader. Rather than copying the
 * data into a new matrix, resulting in two copies of the matrix data, a CC3GLMatrix instance
 * can be initialized to wrap the data.
 *
 * Once initialized, this matrix can be reassigned to wrap a different underlying GL matrix
 * array by setting the value of this property. In this way, a single instance of CC3GLMatrix
 * can be used to manipulate a number of GL matrices.
 *
 * This instance makes no attempt to manage the underlying GL matrix memory. It is up to
 * the application to manage this memory.
 */
+(id) matrixOnGLMatrix: (GLfloat*) aGLMtx;

/**
 * Returns an initialized instance with elements populated from the specified
 * variable arguments, which must consist of 16 elements in column-major order.
 */
-(id) initWithElements: (GLfloat) e00, ...;

/**
 * Allocates and returns an initialized autoreleased instance with elements populated from
 * the specified variable arguments, which must consist of 16 elements in column-major order.
 */
+(id) matrixWithElements: (GLfloat) e00, ...;


#pragma mark -
#pragma mark Instance population

/**
 * Populates this instance from data copied from the specified matrix instance.
 *
 * If the specified matrix is nil, it is treated as the identity matrix, and this
 * matrix will be populated as an identity matrix.
 */
-(void) populateFrom: (CC3GLMatrix*) aMtx;

/**
 * Populates this instance from data copied from the specified GL matrix,
 * which must be a standard 4x4 OpenGL matrix in column-major order.
 */
-(void) populateFromGLMatrix: (GLfloat*) aGLMtx;

/** Populates this instance so that all elements are zero. */
-(void) populateZero;

/** Populates this instance as an identity matrix (ones on the diagonal, zeros elsewhere). */
-(void) populateIdentity;

/**
 * Populates this instance with the translation data provided by the specified translation vector.
 * The resulting matrix can be used to perform translation operations on other matrices through matrix multiplication.
 */
-(void) populateFromTranslation: (CC3Vector) aVector;

/**
 * Populates this instance with the rotation data provided by the specified rotation vector.
 * Each element of the rotation vector represents an Euler angle in degrees,
 * and rotation is performed in YXZ order, which is the OpenGL default.
 *
 * The resulting matrix can be used to perform rotation operations on other matrices
 * through matrix multiplication.
 */
-(void) populateFromRotation: (CC3Vector) aVector;

/**
 * Populates this instance with the rotation data provided by the specified quaternion.
 * The resulting matrix can be used to perform rotation operations on other matrices through matrix multiplication.
 */
-(void) populateFromQuaternion: (CC3Vector4) aQuaternion;

/**
 * Populates this instance with the scaling data provided by the specified scaling vector.
 * The resulting matrix can be used to perform scaling operations on other matrices through matrix multiplication.
 */
-(void) populateFromScale: (CC3Vector) aVector;

/**
 * Populates this matrix so that it will transform a vector pointed down the negative Z-axis to point in
 * the specified forwardDirection, and transforms the positive Y-axis to point in the specified upDirection.
 *
 * When applied to a targetting object (such as a camera, light, gun, etc), this has the effect of
 * pointing that object in a direction and orienting it so that 'up' is in the upDirection.
 *
 * This method works in model-space, and does not include an implied inversion. So, when applied to
 * the camera, this matrix must be subsequently inverted to transform from model-space to view-space.
 */
-(void) populateToPointTowards: (CC3Vector) fwdDirection withUp: (CC3Vector) upDirection;

/**
 * Populates this matrix so that it will transform a vector between the targetLocation and the eyeLocation
 * to point along the negative Z-axis, and transforms the specified upDirection to the positive Y-axis.
 *
 * This transform works in the direction from model-space to view-space, and therefore
 * includes an implied inversion relative to the directToward:withUp: method. When applied to the camera,
 * this has the effect of locating the camera at the eyeLocation and pointing it at the targetLocation,
 * while orienting it so that 'up' appears to be in the upDirection, from the viewer's perspective.
 */
-(void) populateToLookAt: (CC3Vector) targetLocation
			   withEyeAt: (CC3Vector) eyeLocation
				  withUp: (CC3Vector) upDirection;

/** Populates this matrix as a perspective projection matrix with the specified frustum dimensions. */
-(void) populateFromFrustumLeft: (GLfloat) left
					   andRight: (GLfloat) right
					  andBottom: (GLfloat) bottom
						 andTop: (GLfloat) top  
						andNear: (GLfloat) near
						 andFar: (GLfloat) far;

/**
 * Populates this matrix as an infinite-depth perspective projection matrix with the specified
 * frustum dimensions, where the far clipping plane is set at an infinite distance.
 */
-(void) populateFromFrustumLeft: (GLfloat) left
					   andRight: (GLfloat) right
					  andBottom: (GLfloat) bottom
						 andTop: (GLfloat) top  
						andNear: (GLfloat) near;

/** Populates this matrix as a parallel projection matrix with the specified frustum dimensions. */
-(void) populateOrthoFromFrustumLeft: (GLfloat) left
							andRight: (GLfloat) right
						   andBottom: (GLfloat) bottom
							  andTop: (GLfloat) top  
							 andNear: (GLfloat) near
							  andFar: (GLfloat) far;

/**
 * Populates this matrix as an infinite-depth parallel projection matrix with the specified
 * frustum dimensions, where the far clipping plane is set at an infinite distance.
 */
-(void) populateOrthoFromFrustumLeft: (GLfloat) left
							andRight: (GLfloat) right
						   andBottom: (GLfloat) bottom
							  andTop: (GLfloat) top  
							 andNear: (GLfloat) near;


#pragma mark Matrix population

/**
 * Copies all data from the source matrix to the destination matrix.
 * Both matrices must be a standard 4x4 OpenGL matrices in column-major order.
 */
+(void) copyMatrix: (GLfloat*) srcGLMatrix into: (GLfloat*) destGLMatrix;

/**
 * Populates the specified matrix so that it will transform a vector pointed down the negative Z-axis
 * to point in the specified forwardDirection, and transforms the positive Y-axis to point in the
 * specified upDirection. The matrix must be a standard 4x4 OpenGL matrix in column-major order.
 *
 * When applied to a targetting object (such as a camera, light, gun, etc), this has the effect of
 * pointing that object in a direction and orienting it so that 'up' is in the upDirection.
 *
 * This method works in model-space, and does not include an implied inversion. So, when applied to
 * the camera, this matrix must be subsequently inverted to transform from model-space to view-space.
 */
+(void) populate: (GLfloat*) aGLMatrix toPointTowards: (CC3Vector) fwdDirection withUp: (CC3Vector) upDirection;

/**
 * Populates the specified matrix so that it will transform a vector between the targetLocation and
 * the eyeLocation to point along the negative Z-axis, and transforms the specified upDirection to
 * the positive Y-axis. The matrix must be a standard 4x4 OpenGL matrix in column-major order.
 *
 * This transform works in the direction from model-space to view-space, and therefore includes an
 * implied inversion relative to the directToward:withUp: method. When applied to the camera, this
 * has the effect of locating the camera at the eyeLocation and pointing it at the targetLocation,
 * while orienting it so that 'up' appears to be in the upDirection, from the viewer's perspective.
 */
+(void) populate: (GLfloat*) aGLMatrix
		toLookAt: (CC3Vector) targetLocation
	   withEyeAt: (CC3Vector) eyeLocation
		  withUp: (CC3Vector) upDirection;

/**
 * Populates the specified matrix as a perspective projection matrix with the specified
 * frustum dimensions. The matrix must be a standard 4x4 OpenGL matrix in column-major order.
 */
+(void) populate: (GLfloat*) aGLMatrix 
 fromFrustumLeft: (GLfloat) left
		andRight: (GLfloat) right
	   andBottom: (GLfloat) bottom
		  andTop: (GLfloat) top  
		 andNear: (GLfloat) near
		  andFar: (GLfloat) far;

/**
 * Populates the specified matrix as an infinite-depth perspective projection matrix with the
 * specified frustum dimensions, where the far clipping plane is set at an infinite distance.
 * The matrix must be a standard 4x4 OpenGL matrix in column-major order.
 */
+(void) populate: (GLfloat*) aGLMatrix 
 fromFrustumLeft: (GLfloat) left
		andRight: (GLfloat) right
	   andBottom: (GLfloat) bottom
		  andTop: (GLfloat) top  
		 andNear: (GLfloat) near;

/**
 * Populates the specified matrix as a parallel projection matrix with the specified
 * frustum dimensions. The matrix must be a standard 4x4 OpenGL matrix in column-major order.
 */
+(void) populateOrtho: (GLfloat*) aGLMatrix 
	  fromFrustumLeft: (GLfloat) left
			 andRight: (GLfloat) right
			andBottom: (GLfloat) bottom
			   andTop: (GLfloat) top  
			  andNear: (GLfloat) near
			   andFar: (GLfloat) far;

/**
 * Populates the specified matrix as an infinite-depth parallel projection matrix with the
 * specified frustum dimensions, where the far clipping plane is set at an infinite distance.
 * The matrix must be a standard 4x4 OpenGL matrix in column-major order.
 */
+(void) populateOrtho: (GLfloat*) aGLMatrix 
	  fromFrustumLeft: (GLfloat) left
			 andRight: (GLfloat) right
			andBottom: (GLfloat) bottom
			   andTop: (GLfloat) top  
			  andNear: (GLfloat) near;


#pragma mark -
#pragma mark Instance accessing

/**
 * Extracts the rotation component of this matrix and returns it as an Euler rotation vector,
 * assuming the rotations should be applied in YXZ order, which is the OpenGL default.
 * Each element of the returned rotation vector represents an Euler angle in degrees.
 */
-(CC3Vector) extractRotation;

/** Extracts the rotation component of this matrix and returns it as a quaternion. */
-(CC3Vector4) extractQuaternion;

/** Extracts and returns the 'forward' direction vector from the rotation component of this matrix. */
-(CC3Vector) extractForwardDirection;

/** Extracts and returns the 'up' direction vector from the rotation component of this matrix. */
-(CC3Vector) extractUpDirection;

/** Extracts and returns the 'right' direction vector from the rotation component of this matrix. */
-(CC3Vector) extractRightDirection;


#pragma mark Matrix accessing

/**
 * Extracts the rotation component of the specified matrix and returns it as an Euler rotation
 * vector, assuming the rotations should be applied in YXZ order, which is the OpenGL default.
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 * Each element of the returned rotation vector represents an Euler angle in degrees.
 */
+(CC3Vector) extractRotationYXZFromMatrix: (GLfloat*) aGLMatrix;

/**
 * Extracts the rotation component of the specified matrix and returns it as an
 * Euler rotation vector, assuming the rotations should be applied in ZYX order.
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 * Each element of the returned rotation vector represents an Euler angle in degrees.
 */
+(CC3Vector) extractRotationZYXFromMatrix: (GLfloat*) aGLMatrix;

/**
 * Extracts the rotation component of the specified matrix and returns it as a quaternion.
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(CC3Vector4) extractQuaternionFromMatrix: (GLfloat*) aGLMatrix;

/**
 * Extracts and returns the 'forward' direction vector from the rotation component of the specified matrix.
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(CC3Vector) extractForwardDirectionFrom: (GLfloat*) aGLMatrix;

/**
 * Extracts and returns the 'up' direction vector from the rotation component of the specified matrix.
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(CC3Vector) extractUpDirectionFrom: (GLfloat*) aGLMatrix;

/**
 * Extracts and returns the 'right' direction vector from the rotation component of the specified matrix.
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(CC3Vector) extractRightDirectionFrom: (GLfloat*) aGLMatrix;


#pragma mark -
#pragma mark Instance transformations

/**
 * Translates, rotates and scales (in that order) this matrix by the specified amounts.
 * Each element of the rotation vector represents an Euler angle in degrees, and rotation
 * is performed in YXZ order, which is the OpenGL default.
 */
-(void) translateBy: (CC3Vector) translationVector
		   rotateBy: (CC3Vector) rotationVector
			scaleBy: (CC3Vector) scaleVector;
	
/**
 * Rotates this matrix by the specified amount. Each element of the rotation
 * vector represents an Euler angle in degrees, and rotation is performed in
 * YXZ order, which is the OpenGL default.
 *
 * Since this matrix may potentially already contains rotations, the new rotation
 * is performed first, followed by the rotation already contained within this matrix.
 * If the existing rotations were performed first, the new rotation would be performed
 * in the rotated coordinate system defined by this matrix, which is almost always
 * not the desired effect.
 *
 * In mathematical terms, the incoming rotation is converted to matrix form, and is
 * left-multiplied to this matrix. 
 */
-(void) rotateBy: (CC3Vector) aVector;

/**
 * Rotates this matrix around the X-axis by the specified number of degrees.
 *
 * Since this matrix may potentially already contains rotations, the new rotation
 * is performed first, followed by the rotation already contained within this matrix.
 * If the existing rotations were performed first, the new rotation would be performed
 * in the rotated coordinate system defined by this matrix, which is almost always
 * not the desired effect.
 *
 * In mathematical terms, the incoming rotation is converted to matrix form, and is
 * left-multiplied to this matrix. 
 */
-(void) rotateByX: (GLfloat) degrees;

/**
 * Rotates this matrix around the Y-axis by the specified number of degrees.
 *
 * Since this matrix may potentially already contains rotations, the new rotation
 * is performed first, followed by the rotation already contained within this matrix.
 * If the existing rotations were performed first, the new rotation would be performed
 * in the rotated coordinate system defined by this matrix, which is almost always
 * not the desired effect.
 *
 * In mathematical terms, the incoming rotation is converted to matrix form, and is
 * left-multiplied to this matrix. 
 */
-(void) rotateByY: (GLfloat) degrees;

/**
 * Rotates this matrix around the Z-axis by the specified number of degrees.
 *
 * Since this matrix may potentially already contains rotations, the new rotation
 * is performed first, followed by the rotation already contained within this matrix.
 * If the existing rotations were performed first, the new rotation would be performed
 * in the rotated coordinate system defined by this matrix, which is almost always
 * not the desired effect.
 *
 * In mathematical terms, the incoming rotation is converted to matrix form, and is
 * left-multiplied to this matrix. 
 */
-(void) rotateByZ: (GLfloat) degrees;

/**
 * Rotates this matrix by the rotation specified in the given quaternion.
 *
 * Since this matrix may potentially already contains rotations, the new rotation
 * is performed first, followed by the rotation already contained within this matrix.
 * If the existing rotations were performed first, the new rotation would be performed
 * in the rotated coordinate system defined by this matrix, which is almost always
 * not the desired effect.
 *
 * In mathematical terms, the incoming rotation is converted to matrix form, and is
 * left-multiplied to this matrix. 
 */
-(void) rotateByQuaternion: (CC3Vector4) aQuaternion;

/**
 * Orthonormalizes the three basis vectors of this matrix, using a Gram-Schmidt process.
 *
 * Upon completion, each basis vector in this matrix will be a unit vector that
 * is orthagonal to the other two basis vectors in this matrix.
 *
 * For a 4x4 GL matrix, each basis vector is made up of the first three elements of
 * one of the first three columns. The first, second and third columns are the basis
 * vector of the X, Y & Z axes, respectively.
 *
 * The starting point for orthonormalization is indicated by the specified start vector.
 * Since the Gram-Schmidt process is biased towards the starting vector, if this method
 * will be invoked repeatedly on the same matrix, it is recommended that the starting
 * vector be changed on each invocation of this method, to ensure that the starting
 * bias be averaged across each of the basis vectors over the long term.
 */
-(void) orthonormalizeRotationStartingWith: (CC3GLMatrixOrthonormalizationStart) startVector;

/** Translates this matrix in three dimensions by the specified translation vector. */
-(void) translateBy: (CC3Vector) aVector;

/** Translates this matrix along the X-axis by the specified amount. */
-(void) translateByX: (GLfloat) distance;

/** Translates this matrix along the Y-axis by the specified amount. */
-(void) translateByY: (GLfloat) distance;

/** Translates this matrix along the Z-axis by the specified amount. */
-(void) translateByZ: (GLfloat) distance;

/**
 * Scales this matrix in three dimensions by the specified scaling vector. Non-uniform scaling
 * can be achieved by specifying different values for each element of the scaling vector.
 */
-(void) scaleBy: (CC3Vector) aVector;

/** Scales this matrix along the X-axis by the specified factor. */
-(void) scaleByX: (GLfloat) scaleFactor;

/** Scales this matrix along the Y-axis by the specified factor. */
-(void) scaleByY: (GLfloat) scaleFactor;

/** Scales this matrix along the Z-axis by the specified factor. */
-(void) scaleByZ: (GLfloat) scaleFactor;

/** Scales this matrix uniformly in three dimensions by the specified factor. */
-(void) scaleUniformlyBy: (GLfloat) scaleFactor;


#pragma mark Matrix transformations

/**
 * Translates, rotates and scales (in that order) the specified matrix by the specified amounts.
 * Each element of the rotation vector represents an Euler angle in degrees, and rotation
 * is performed in YXZ order, which is the OpenGL default.
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(void) transform: (GLfloat*) aGLMatrix
	  translateBy: (CC3Vector) aTranslation
		 rotateBy: (CC3Vector) aRotation
		  scaleBy: (CC3Vector) aScale;

/**
 * Rotates the specified matrix by the specified amount. Each element of the rotation
 * vector represents an Euler angle in degrees, and rotation is performed in YXZ order,
 * which is the OpenGL default.
 *
 * Since this operation rotates a matrix that potentially already contains rotations,
 * the new rotation is performed first, followed by the rotation already contained
 * within the specified matrix. If the matrix rotations were performed first, the new
 * rotation would be performed in the rotated coordinate system defined by the matrix.
 *
 * In mathematical terms, the incoming rotation is converted to matrix form, and is
 * left-multiplied to the specified matrix. 
 *
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(void) rotateYXZ: (GLfloat*) aGLMatrix by: (CC3Vector) aRotation;
	
/**
 * Rotates the specified matrix by the specified amount. Each element of the rotation
 * vector represents an Euler angle in degrees, and rotation is performed in XYZ order.
 *
 * Since this operation rotates a matrix that potentially already contains rotations,
 * the new rotation is performed first, followed by the rotation already contained
 * within the specified matrix. If the matrix rotations were performed first, the new
 * rotation would be performed in the rotated coordinate system defined by the matrix.
 *
 * In mathematical terms, the incoming rotation is converted to matrix form, and is
 * left-multiplied to the specified matrix. 
 *
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(void) rotateZYX: (GLfloat*) aGLMatrix by: (CC3Vector) aRotation;

/**
 * Rotates the specified matrix around the X-axis by the specified number of degrees.
 *
 * Since this operation rotates a matrix that potentially already contains rotations,
 * the new rotation is performed first, followed by the rotation already contained
 * within the specified matrix. If the matrix rotations were performed first, the new
 * rotation would be performed in the rotated coordinate system defined by the matrix.
 *
 * In mathematical terms, the incoming rotation is converted to matrix form, and is
 * left-multiplied to the specified matrix. 
 *
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(void) rotate: (GLfloat*) aGLMatrix byX: (GLfloat) degrees;

/**
 * Rotates the specified matrix around the Y-axis by the specified number of degrees.
 *
 * Since this operation rotates a matrix that potentially already contains rotations,
 * the new rotation is performed first, followed by the rotation already contained
 * within the specified matrix. If the matrix rotations were performed first, the new
 * rotation would be performed in the rotated coordinate system defined by the matrix.
 *
 * In mathematical terms, the incoming rotation is converted to matrix form, and is
 * left-multiplied to the specified matrix. 
 *
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(void) rotate: (GLfloat*) aGLMatrix byY: (GLfloat) degrees;

/**
 * Rotates the specified matrix around the Z-axis by the specified number of degrees.
 *
 * Since this operation rotates a matrix that potentially already contains rotations,
 * the new rotation is performed first, followed by the rotation already contained
 * within the specified matrix. If the matrix rotations were performed first, the new
 * rotation would be performed in the rotated coordinate system defined by the matrix.
 *
 * In mathematical terms, the incoming rotation is converted to matrix form, and is
 * left-multiplied to the specified matrix. 
 *
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(void) rotate: (GLfloat*) aGLMatrix byZ: (GLfloat) degrees;

/**
 * Rotates the specified matrix by the rotation specified in the given quaternion.
 *
 * Since this operation rotates a matrix that potentially already contains rotations,
 * the new rotation is performed first, followed by the rotation already contained
 * within the specified matrix. If the matrix rotations were performed first, the new
 * rotation would be performed in the rotated coordinate system defined by the matrix.
 *
 * In mathematical terms, the incoming rotation is converted to matrix form, and is
 * left-multiplied to the specified matrix. 
 *
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(void) rotate: (GLfloat*) aGLMatrix byQuaternion: (CC3Vector4) aQuaternion;

/**
 * Orthonormalizes the three basis vectors of the specified matrix, using a Gram-Schmidt process.
 *
 * Upon completion, each basis vector in the specified matrix will be a unit vector that
 * is orthagonal to the other two basis vectors in that matrix.
 *
 * For a 4x4 GL matrix, each basis vector is made up of the first three elements of
 * one of the first three columns. The first, second and third columns are the basis
 * vector of the X, Y & Z axes, respectively.
 *
 * The starting point for orthonormalization is indicated by the specified start vector.
 * Since the Gram-Schmidt process is biased towards the starting vector, if this method
 * will be invoked repeatedly on the same matrix, it is recommended that the starting
 * vector be changed on each invocation of this method, to ensure that the starting
 * bias be averaged across each of the basis vectors over the long term.
 */
+(void) orthonormalizeRotationOf: (GLfloat*) aGLMatrix
					startingWith: (CC3GLMatrixOrthonormalizationStart) startVector;

/**
 * Translates this matrix in three dimensions by the specified translation vector.
 *
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(void) translate: (GLfloat*) aGLMatrix by: (CC3Vector) aVector;

/**
 * Translates this matrix along the X-axis by the specified amount.
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(void) translate: (GLfloat*) aGLMatrix byX: (GLfloat) distance;

/**
 * Translates this matrix along the Y-axis by the specified amount.
 *
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(void) translate: (GLfloat*) aGLMatrix byY: (GLfloat) distance;

/**
 * Translates this matrix along the Z-axis by the specified amount.
 *
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(void) translate: (GLfloat*) aGLMatrix byZ: (GLfloat) distance;

/**
 * Scales this matrix in three dimensions by the specified scaling vector.
 * Non-uniform scaling can be achieved by specifying different values for
 * each element of the scaling vector.
 *
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(void) scale: (GLfloat*) aGLMatrix by: (CC3Vector) aVector;

/**
 * Scales this matrix along the X-axis by the specified factor.
 *
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(void) scale: (GLfloat*) aGLMatrix byX: (GLfloat) scaleFactor;

/**
 * Scales this matrix along the Y-axis by the specified factor.
 *
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(void) scale: (GLfloat*) aGLMatrix byY: (GLfloat) scaleFactor;

/**
 * Scales this matrix along the Z-axis by the specified factor.
 *
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(void) scale: (GLfloat*) aGLMatrix byZ: (GLfloat) scaleFactor;

/**
 * Scales this matrix uniformly in three dimensions by the specified factor.
 *
 * The matrix must be standard 4x4 OpenGL matrix in column-major order.
 */
+(void) scale: (GLfloat*) aGLMatrix uniformlyBy: (GLfloat) scaleFactor;


#pragma mark -
#pragma mark Instance math operations

/**
 * Multiplies a matrix by the specified matrix, where, in the matrix multiplication
 * equation, this matrix is on the left, and the specified matrix is on the right.
 *
 * The contents of this matrix are changed.
 * The contents of the specified matrix remain unchanged.
 *
 * If the specified matrix is nil, it is treated as an identity matrix,
 * and this matrix remains unchanged.
 */
-(void) multiplyByMatrix: (CC3GLMatrix*) aMatrix;

/**
 * Multiplies a matrix by the specified matrix, where, in the matrix multiplication
 * equation, the specified matrix is on the left and this matrix is on the right.
 *
 * The contents of this matrix are changed.
 * The contents of the specified matrix remain unchanged.
 *
 * If the specified matrix is nil, it is treated as an identity matrix,
 * and this matrix remains unchanged.
 */
-(void) leftMultiplyByMatrix: (CC3GLMatrix*) aMatrix;

/**
 * Transforms the specified location vector using this matrix, and returns the transformed location.
 * During multiplication, the fourth element of the location vector is assumed to have a value of one.
 * This matrix and the original specified location vector remain unchanged.
 */
-(CC3Vector) transformLocation: (CC3Vector) aLocation;

/**
 * Transforms the specified direction vector using this matrix, and returns the transformed direction.
 * During multiplication, the fourth element of the direction vector is assumed to have a value of zero.
 * This matrix and the original specified direction vector remain unchanged.
 */
-(CC3Vector) transformDirection: (CC3Vector) aDirection;

/**
 * Transforms the specified homogeneous vector using this matrix, and returns the transformed homogeneous vector.
 * This matrix and the original specified homogeneous vector remain unchanged.
 */
-(CC3Vector4) transformHomogeneousVector: (CC3Vector4) aVector;

/**
 * Transforms the specified ray using this matrix, and returns the transformed ray.
 *
 * Since a ray is a composite of a location and a direction, this implementation invokes
 * the transformLocation: method on the location component of the ray, and the
 * transformDirection: method on the direction component of the ray.
 *
 * This matrix and the original specified direction vector remain unchanged.
 */
-(CC3Ray) transformRay: (CC3Ray) aRay;

/** Transposes this matrix. The contents of this matrix are changed. */
-(void) transpose;

/**
 * Inverts this matrix by using the algorithm of calculating the classical adjoint
 * and dividing by the determinant. The contents of the matrix are changed.
 *
 * Not all matrices are invertable. Returns whether the matrix was inverted. If this method
 * returns NO, then the matrix was not inverted and remains in the state it was when this
 * method was invoked.
 *
 * Matrix inversion is an computationally-expensive algorithm. If it is known that the matrix
 * contains only rotation and translation, use the invertRigid method instead, which is
 * between one and two orders of magnitude faster than this method.
 * 
 * Also, be aware that rounding inaccuracies accumulated during the inversion calculations can
 * often result in the inverse matrix that is not affine (the bottom row of the matrix is not
 * {0, 0, 0, 1}), even when the initial matrix was affine. These accumulated errors can often
 * be significant when applied to the bottom row and will affect further calculations.
 * 
 * If it is known that a matrix represents an affine transformation, use the invertAffine
 * method instead, which forces the bottom row back to {0, 0, 0, 1} after the inversion
 * to maintain the inverted matrix as an affine transformation.
 *
 * Affine transforms include all combinations of rotation, scaling, shearing, translation,
 * and orthographic projection, so all matrices encountered while working with 3D graphics,
 * with the exception of perspective projection, will be affine transforms. Unless you are
 * working with the projection matrix, or a custom, non-affine matrix, it is recommended
 * that you use invertAffine instead of this method.
 */
-(BOOL) invert;

/**
 * Inverts this matrix by using the algorithm of calculating the classical adjoint
 * and dividing by the determinant. The contents of the matrix are changed.
 *
 * Not all matrices are invertable. Returns whether the matrix was inverted. If this method
 * returns NO, then the matrix was not inverted and remains in the state it was when this
 * method was invoked.
 *
 * Matrix inversion is an computationally-expensive algorithm. If it is known that the
 * matrix contains only rotation and translation, use the invertRigid method instead,
 * which is between one and two orders of magnitude faster than this method.
 *
 * This method uses the invert: method, but differs in that it assumes that the matrix
 * represents an affine transform (the bottom row of the matrix is {0, 0, 0, 1}), and
 * that accumulated inaccuracies in the inversion calculations should be removed from
 * the bottom row of the resulting inverted matrix. After inversion, the bottom row of
 * the inverted matrix is forced back to exactly {0, 0, 0, 1}.
 *
 * This can be quite useful, as this row is particularly sensitive to the accumulation of
 * inaccuracies and can often have a drastic impact on the accuracy of subsequent matrix
 * and vector calculations. If it is known that a matrix represents an affine transformation,
 * use this method instead of the invert method.
 * 
 * Affine transforms include all combinations of rotation, scaling, shearing, translation,
 * and orthographic projection, so all matrices encountered while working with 3D graphics,
 * with the exception of perspective projection, will be affine transforms.  Unless you are
 * working with the projection matrix, or a custom, non-affine matrix, it is recommended
 * that you use this method instead of the invert method.
 */
-(BOOL) invertAffine;

/**
 * Inverts this matrix using transposition and translation. The contents of this matrix
 * are changed.
 *
 * This method assumes that the matrix represents a rigid transformation, containing only
 * rotation and translation. Use this method only if it is known that this is the case.
 *
 * Inversion of a rigid transform matrix can be accomplished very quickly using transposition
 * and translation, and is consistently one to two orders of magnitude faster than using
 * either the invert or invertAffine methods. It is recommended that this method be used
 * wherever possible.
 */
-(void) invertRigid;
	

#pragma mark Matrix math operations

/**
 * Multiplies a matrix by another matrix, where, in the matrix multiplication
 * equation, the first matrix is on the left and the second matrix is on the right.
 *
 * The contents of the first matrix are changed. The contents of the second
 * matrix remain unchanged.
 * 
 * Both matrices must be a standard 4x4 OpenGL matrices in column-major order.
 */
+(void) multiply: (GLfloat*) aGLMatrix byMatrix: (GLfloat*) anotherGLMatrix;

/**
 * Multiplies a matrix by another matrix, where, in the matrix multiplication
 * equation, the first matrix is on the right and the second matrix is on the left.
 *
 * The contents of the first matrix are changed. The contents of the second
 * matrix remain unchanged.
 * 
 * Both matrices must be a standard 4x4 OpenGL matrices in column-major order.
 */
+(void) leftMultiply: (GLfloat*) aGLMatrix byMatrix: (GLfloat*) anotherGLMatrix;

/**
 * Transforms the specified location vector using the specified matrix, and returns the transformed
 * location. During multiplication, the fourth element of the location vector is assumed to have a
 * value of one. The matrix and the original specified location vector remain unchanged.
 * The matrix must be a standard 4x4 OpenGL matrix in column-major order.
 */
+(CC3Vector) transformLocation: (CC3Vector) aLocation withMatrix: (GLfloat*) aGLMatrix;

/**
 * Transforms the specified direction vector using the specified matrix, and returns the transformed
 * direction. During multiplication, the fourth element of the location vector is assumed to have a
 * value of zero. The matrix and the original specified direction vector remain unchanged.
 * The matrix must be a standard 4x4 OpenGL matrix in column-major order.
 */
+(CC3Vector) transformDirection: (CC3Vector) aDirection withMatrix: (GLfloat*) aGLMatrix;

/**
 * Transforms the specified homogeneous vector using the specified matrix, and returns the transformed
 * homogeneous vector. The matrix and the original specified homogeneous vector remain unchanged.
 * The matrix must be a standard 4x4 OpenGL matrix in column-major order.
 */
+(CC3Vector4) transformHomogeneousVector: (CC3Vector4) aVector withMatrix: (GLfloat*) aGLMatrix;

/**
 * Transforms the specified ray using this matrix, and returns the transformed ray.
 *
 * Since a ray is a composite of a location and a direction, this implementation invokes
 * the transformLocation:withMatrix: method on the location component of the ray, and the
 * transformDirection:withMatrix: method on the direction component of the ray.
 *
 * This matrix and the original specified direction vector remain unchanged.
 */
+(CC3Ray) transformRay: (CC3Ray) aRay withMatrix: (GLfloat*) aGLMatrix;

/**
 * Transposes the specified matrix. The contents of the matrix are changed.
 * The matrix must be a standard 4x4 OpenGL matrix in column-major order.
 */
+(void) transpose: (GLfloat*) aGLMatrix;

/**
 * Inverts the specified matrix by using the algorithm of calculating the classical adjoint
 * and dividing by the determinant. The contents of the matrix are changed. The matrix must
 * be a standard 4x4 OpenGL matrix in column-major order.
 *
 * Not all matrices are invertable. Returns whether the matrix was inverted. If this method
 * returns NO, then the matrix was not inverted and remains in the state it was when this
 * method was invoked.
 *
 * Matrix inversion is an computationally-expensive algorithm. If it is known that the matrix
 * contains only rotation and translation, use the invertRigid: method instead, which is
 * between one and two orders of magnitude faster than this method.
 * 
 * Also, be aware that rounding inaccuracies accumulated during the inversion calculations can
 * often result in the inverse matrix that is not affine (the bottom row of the matrix is not
 * {0, 0, 0, 1}), even when the initial matrix was affine. These accumulated errors can often
 * be significant when applied to the bottom row and will affect further calculations.
 * 
 * If it is known that a matrix represents an affine transformation, use the invertAffine:
 * method instead, which forces the bottom row back to {0, 0, 0, 1} after the inversion
 * to maintain the inverted matrix as an affine transformation.
 *
 * Affine transforms include all combinations of rotation, scaling, shearing, translation,
 * and orthographic projection, so all matrices encountered while working with 3D graphics,
 * with the exception of perspective projection, will be affine transforms. Unless you are
 * working with the projection matrix, or a custom, non-affine matrix, it is recommended
 * that you use invertAffine: instead of this method.
 */
+(BOOL) invert: (GLfloat*) aGLMatrix;

/**
 * Inverts the specified matrix by using the algorithm of calculating the classical adjoint
 * and dividing by the determinant. The contents of the matrix are changed. The matrix must
 * be a standard 4x4 OpenGL matrix in column-major order.
 *
 * Not all matrices are invertable. Returns whether the matrix was inverted. If this method
 * returns NO, then the matrix was not inverted and remains in the state it was when this
 * method was invoked.
 *
 * Matrix inversion is an computationally-expensive algorithm. If it is known that the
 * matrix contains only rotation and translation, use the invertRigid: method instead,
 * which is between one and two orders of magnitude faster than this method.
 *
 * This method uses the invert: method, but differs in that it assumes that the matrix
 * represents an affine transform (the bottom row of the matrix is {0, 0, 0, 1}), and
 * that accumulated inaccuracies in the inversion calculations should be removed from
 * the bottom row of the resulting inverted matrix. After inversion, the bottom row of
 * the inverted matrix is forced back to exactly {0, 0, 0, 1}.
 *
 * This can be quite useful, as this row is particularly sensitive to the accumulation of
 * inaccuracies and can often have a drastic impact on the accuracy of subsequent matrix
 * and vector calculations. If it is known that a matrix represents an affine transformation,
 * use this method instead of the invert: method.
 * 
 * Affine transforms include all combinations of rotation, scaling, shearing, translation,
 * and orthographic projection, so all matrices encountered while working with 3D graphics,
 * with the exception of perspective projection, will be affine transforms.  Unless you are
 * working with the projection matrix, or a custom, non-affine matrix, it is recommended
 * that you use this method instead of the invert: method.
 */
+(BOOL) invertAffine: (GLfloat*) aGLMatrix;

/**
 * Inverts the specified matrix using transposition and translation. The contents of this
 * matrix are changed. The matrix must be a standard 4x4 OpenGL matrix in column-major order.
 *
 * This method assumes that the matrix represents a rigid transformation, containing only
 * rotation and translation. Use this method only if it is known that this is the case.
 *
 * Inversion of a rigid transform matrix can be accomplished very quickly using transposition
 * and translation, and is consistently one to two orders of magnitude faster than using
 * either the invert: or invertAffine: methods. It is recommended that this method be used
 * wherever possible.
 */
+(void) invertRigid: (GLfloat*) aGLMatrix;

@end
