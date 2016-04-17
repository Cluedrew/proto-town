#ifndef UTILS_HPP
#define UTILS_HPP

/* The home for everything else, small scattered functions.
 *
 * This is sort of an experament, so I'm going to give myself some guidlines
 * on what "everything else" is.
 * 1. If it makes sense somewhere else, put it there.
 * 2. Types and other things that would be included from headers should be
 *    put in their own small headers.
 * 3. Large blocks of related functions should be considered for their own
 *    header.
 */


float blocksToPixels (int blocks);
/* Convert block units to pixel units, adjusting magnatude.
 * Params: The messurement in blocks.
 * Return: The messurement in pixels.
 */

int pixelsToBlocks (float pixels);
/* Convert pixel units to block units, adjusting magnatude.
 * Params: The messurement in pixels.
 * Return: The messurement in blocks.
 */

bool aEq (float lhs, float rhs, float diff);
/* Approximatly equals, check if lhs & rhs differ by diff or less.
 * Params: lhs & rhs can be any two floats, diff must be non-negative.
 * Return: True if lhs & rhs are approximatly equal, false otherwise.
 */

#endif//UTILS_HPP
