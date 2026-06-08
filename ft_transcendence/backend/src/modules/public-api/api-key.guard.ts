/**
 * ============================================
 * API KEY GUARD - Securite cle API publique
 * ============================================
 *
 * Protege les routes /api/public/* avec une cle API
 * stockee dans la variable d'environnement PUBLIC_API_KEY.
 *
 * Cette cle est SEPAREE de l'authentification JWT :
 * - JWT = identifie un utilisateur connecte (humain)
 * - API Key = identifie une application/script tiers
 *
 * Usage : ajouter le header `x-api-key: <cle>` a la requete.
 */

import {
  CanActivate,
  ExecutionContext,
  Injectable,
  UnauthorizedException,
} from '@nestjs/common';
import { ConfigService } from '@nestjs/config';

@Injectable()
export class ApiKeyGuard implements CanActivate {
  constructor(private readonly configService: ConfigService) {}

  canActivate(context: ExecutionContext): boolean {
    const request = context.switchToHttp().getRequest();
    const apiKey = request.headers['x-api-key'];
    const expected = this.configService.get<string>('PUBLIC_API_KEY');

    if (!expected) {
      throw new UnauthorizedException(
        'API key non configuree cote serveur (PUBLIC_API_KEY manquante)',
      );
    }

    if (!apiKey || apiKey !== expected) {
      throw new UnauthorizedException('Cle API invalide ou manquante');
    }

    return true;
  }
}
