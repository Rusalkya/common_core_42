/**
 * ============================================
 * PRISMA SERVICE - Connexion a la base de donnees
 * ============================================
 * 
 * Service global qui gere la connexion PostgreSQL via Prisma ORM.
 * - Se connecte automatiquement au demarrage de l'app
 * - Se deconnecte proprement a l'arret
 * - Logs actives pour le debug
 * 
 * Utilisation dans les services :
 *   constructor(private readonly prisma: PrismaService) {}
 *   this.prisma.user.findMany() // Exemple de requete
 * 
 * Le schema est defini dans prisma/schema.prisma
 * 
 * Responsable: wtohami- (Backend) + rgalmich (Schema)
 */

import { Injectable, OnModuleInit, OnModuleDestroy } from '@nestjs/common';
import { PrismaClient } from '@prisma/client';

@Injectable()
export class PrismaService extends PrismaClient implements OnModuleInit, OnModuleDestroy {
  constructor() {
    super({
      log: ['query', 'info', 'warn', 'error'], // Active les logs SQL pour debug
    });
  }

  // Connexion automatique au demarrage du module
  async onModuleInit() {
    try {
      await this.$connect();
      console.log(' Prisma connecte a la base de donnees');
    } catch (error) {
      console.warn('  Base de donnees non disponible - Mode test sans BDD');
      console.warn('   Pour connecter la BDD, lance: docker-compose up -d db');
    }
  }

  // Deconnexion propre a l'arret
  async onModuleDestroy() {
    await this.$disconnect();
    console.log('🔌 Prisma deconnecte');
  }
}
