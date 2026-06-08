import {
  PipeTransform,
  Injectable,
  ArgumentMetadata,
  BadRequestException,
} from '@nestjs/common';

/**
 * ParseIntPipe personnalise - Convertit un string en number
 * 
 * UTILISATION:
 * @Get(':id')
 * findOne(@Param('id', ParseIntPipe) id: number) {}
 * 
 * DOCUMENTATION:
 * - https://docs.nestjs.com/pipes#custom-pipes
 */

@Injectable()
export class ParseIntPipe implements PipeTransform<string, number> {
  /**
   * @param value - La valeur recue (ex: "123")
   * @param metadata - Infos sur le parametre (type, data, metatype)
   * @returns Le number converti
   */
  transform(value: string, metadata: ArgumentMetadata): number {
    // Convertir value en number (base 10)
    const val = parseInt(value, 10);

    // Verifier si c'est un nombre valide
    if (isNaN(val)) {
      throw new BadRequestException(
        `Validation failed: "${value}" is not a valid integer`,
      );
    }

    // Retourner le nombre converti
    return val;
  }
}
