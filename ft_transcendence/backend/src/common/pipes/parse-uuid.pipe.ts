import {
  PipeTransform,
  Injectable,
  ArgumentMetadata,
  BadRequestException,
} from '@nestjs/common';

/**
 * ParseUUIDPipe personnalise - Valide qu'une string est un UUID valide
 * 
 * FORMAT UUID v4:
 * xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx
 * Exemple: "550e8400-e29b-41d4-a716-446655440000"
 * 
 * UTILISATION:
 * @Get(':id')
 * findOne(@Param('id', ParseUUIDPipe) id: string) {}
 */

@Injectable()
export class ParseUUIDPipe implements PipeTransform<string, string> {
  // Regex pour valider un UUID (toutes versions)
  private readonly uuidRegex =
    /^[0-9a-f]{8}-[0-9a-f]{4}-[1-5][0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$/i;

  transform(value: string, metadata: ArgumentMetadata): string {
    // Verifier si value est un string
    if (typeof value !== 'string') {
      throw new BadRequestException('Validation failed: UUID must be a string');
    }

    // Verifier si value correspond au format UUID
    if (!this.uuidRegex.test(value)) {
      throw new BadRequestException(
        `Validation failed: "${value}" is not a valid UUID`,
      );
    }

    // Retourner la valeur validee (en minuscules pour uniformite)
    return value.toLowerCase();
  }
}
