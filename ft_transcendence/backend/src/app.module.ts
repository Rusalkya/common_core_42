/**
 * ============================================
 * APP MODULE - Module racine de l'application
 * ============================================
 * 
 * C'est le module principal qui importe tous les autres modules.
 * NestJS demarre a partir de ce module.
 * 
 * Modules importes :
 * - ConfigModule : Variables d'environnement (.env)
 * - PrismaModule : Connexion base de donnees
 * - AuthModule   : Authentification (login, register)
 * - UsersModule  : Gestion des utilisateurs
 * - PostsModule  : Publications et likes
 * - CommentsModule : Commentaires
 * - FriendsModule : Systeme d'amis
 * - MessagesModule : Messagerie privee
 * - NotificationsModule : Alertes
 * - ChatModule   : WebSocket temps reel
 * - UploadModule : Upload d'images
 * - HealthModule : Health checks
 * 
 * Responsable: wtohami- (Backend)
 */

import { Module } from '@nestjs/common';
import { ConfigModule } from '@nestjs/config';
import { ThrottlerModule } from '@nestjs/throttler';
import { APP_GUARD } from '@nestjs/core';
import { ThrottlerGuard } from './common/guards';

// Prisma (Base de donnees)
import { PrismaModule } from './prisma';

// Modules fonctionnels
import { AuthModule } from './modules/auth/auth.module';
import { UsersModule } from './modules/users/users.module';
import { PostsModule } from './modules/posts/posts.module';
import { CommentsModule } from './modules/comments/comments.module';
import { FriendsModule } from './modules/friends/friends.module';
import { MessagesModule } from './modules/messages/messages.module';
import { NotificationsModule } from './modules/notifications/notifications.module';
import { ChatModule } from './modules/chat/chat.module';
import { UploadModule } from './modules/upload/upload.module';
import { HealthModule } from './modules/health/health.module';
import { MetricsModule } from './modules/metrics/metrics.module';
import { PublicApiModule } from './modules/public-api/public-api.module';

@Module({
  imports: [
    // Configuration globale (variables d'environnement)
    ConfigModule.forRoot({
      isGlobal: true,
      envFilePath: '.env',
    }),

    // ========================================
    // RATE LIMITING - Protection brute-force
    // ========================================
    ThrottlerModule.forRoot([
      {
        name: 'global',
        ttl: 60000, // 60 secondes
        limit: 100, // 100 requetes par minute
      },
      {
        name: 'auth',
        ttl: 60000,
        limit: process.env.NODE_ENV === 'production' ? 5 : 1000,
      },
    ]),

    // Base de donnees
    PrismaModule,

    // Modules de l'application
    AuthModule,
    UsersModule,
    PostsModule,
    CommentsModule,
    FriendsModule,
    MessagesModule,
    NotificationsModule,
    ChatModule,
    UploadModule,
    HealthModule,
    MetricsModule,
    PublicApiModule,
  ],
  controllers: [],
  providers: [
    // ========================================
    // Active le rate limiting globalement
    // ========================================
    {
      provide: APP_GUARD,
      useClass: ThrottlerGuard,
    },
  ],
})
export class AppModule {}
