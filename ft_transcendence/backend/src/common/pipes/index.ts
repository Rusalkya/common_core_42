/**
 * Barrel file - Exporte tous les Pipes
 * 
 * UTILISATION:
 * import { ParseIntPipe, TrimPipe, validationPipeConfig } from './common/pipes';
 * 
 * QU'EST-CE QU'UN PIPE ?
 * - Transformation: convertir les donnees (string → number)
 * - Validation: verifier que les donnees sont valides
 * 
 * PIPES BUILT-IN DE NESTJS:
 * - ValidationPipe (validation avec class-validator)
 * - ParseIntPipe, ParseFloatPipe, ParseBoolPipe
 * - ParseUUIDPipe, ParseEnumPipe, ParseArrayPipe
 * 
 * DOCUMENTATION:
 * - https://docs.nestjs.com/pipes
 */

export * from './validation.config';
export * from './parse-int.pipe';
export * from './trim.pipe';
export * from './parse-uuid.pipe';
export * from './sanitize.pipe';
