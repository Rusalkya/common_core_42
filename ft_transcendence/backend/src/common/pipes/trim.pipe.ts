import {
  PipeTransform,
  Injectable,
  ArgumentMetadata,
} from '@nestjs/common';

/**
 * TrimPipe - Supprime les espaces au debut et a la fin des strings
 * 
 * UTILISATION:
 * @Post()
 * create(@Body(TrimPipe) dto: CreateUserDto) {}
 * 
 * EXEMPLE:
 * Input:  { name: "  John  ", email: "  john@example.com  " }
 * Output: { name: "John", email: "john@example.com" }
 */

@Injectable()
export class TrimPipe implements PipeTransform {
  transform(value: unknown, metadata: ArgumentMetadata): unknown {
    // Si c'est un string, appliquer trim()
    if (typeof value === 'string') {
      return value.trim();
    }

    // Si c'est un objet, parcourir ses proprietes et trim les strings
    if (typeof value === 'object' && value !== null) {
      const trimmedObject: Record<string, unknown> = {};

      // Parcourir chaque propriete de l'objet
      for (const [key, val] of Object.entries(value)) {
        // Si la valeur est un string, la trim
        if (typeof val === 'string') {
          trimmedObject[key] = val.trim();
        } else {
          // Sinon, garder la valeur telle quelle
          trimmedObject[key] = val;
        }
      }

      return trimmedObject;
    }

    // Si ce n'est ni string ni objet, retourner tel quel
    return value;
  }
}
