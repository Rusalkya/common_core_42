/**
 * ============================================
 * MAIN.TS - Point d'entree de l'application
 * ============================================
 * 
 * Ce fichier configure et demarre le serveur NestJS :
 * - CORS pour autoriser le frontend
 * - Validation globale des DTOs
 * - Documentation Swagger sur /api/docs
 * - Prefixe global /api pour toutes les routes
 * 
 * Pour lancer : npm run start:dev
 * API disponible sur : http://localhost:3001/api
 * Swagger disponible sur : http://localhost:3001/api/docs
 * 
 * Responsable: wtohami- (Backend)
 */

import { NestFactory } from '@nestjs/core';
import { ConfigService } from '@nestjs/config';
import { DocumentBuilder, SwaggerModule } from '@nestjs/swagger';
import { AppModule } from './app.module';
import { AllExceptionsFilter } from './common/filters';
import { TransformInterceptor, LoggingInterceptor } from './common/interceptors';
import { SecurityLoggingInterceptor } from './common/interceptors/security-logging.interceptor';
import { createValidationPipe } from './common/pipes';
import helmet from 'helmet';


async function bootstrap() {
  // 1. Creer l'application NestJS a partir du module racine
  const app = await NestFactory.create(AppModule);
  
  // ========================================
  // SECURITE - HELMET (Headers HTTP securises)
  // ========================================
  app.use(helmet({
    contentSecurityPolicy: {
      directives: {
        defaultSrc: ["'self'"],
        styleSrc: ["'self'", "'unsafe-inline'"],
        scriptSrc: ["'self'"],
        imgSrc: ["'self'", 'data:', 'https:'],
      },
    },
    hsts: {
      maxAge: 31536000,
      includeSubDomains: true,
      preload: true,
    },
  }));

  // Filtres et intercepteurs
  app.useGlobalFilters(new AllExceptionsFilter());
  app.useGlobalPipes(createValidationPipe());
  app.useGlobalInterceptors(
    new LoggingInterceptor(),
    new TransformInterceptor(),
    new SecurityLoggingInterceptor(), // 🔐 Logging de securite
  );
  
  // Recuperer le service de configuration
  const configService = app.get(ConfigService);

  // ========================================
  // CORS STRICT avec whitelist
  // ========================================
  const allowedOrigins = (configService.get<string>('CORS_ORIGIN') || 'http://localhost:5173').split(',');
  
  app.enableCors({
    origin: (origin, callback) => {
      // Permet les requetes sans origin (ex: Postman, curl)
      if (!origin) return callback(null, true);
      
      if (allowedOrigins.includes(origin)) {
        callback(null, true);
      } else {
        console.warn(`⚠️  CORS blocked origin: ${origin}`);
        callback(new Error('Not allowed by CORS'));
      }
    },
    methods: ['GET', 'POST', 'PUT', 'PATCH', 'DELETE', 'OPTIONS'],
    credentials: true,
    allowedHeaders: ['Content-Type', 'Authorization', 'X-Requested-With', 'x-api-key'],
    exposedHeaders: ['Authorization'],
  });

  // Prefix global pour toutes les routes API
  app.setGlobalPrefix('api');

  // Configuration Swagger pour la documentation API
  const swaggerConfig = new DocumentBuilder()
    .setTitle('Trans API')
    .setDescription('API backend pour l\'application Trans - Reseau social')
    .setVersion('1.0')
    .addBearerAuth(
      {
        type: 'http',
        scheme: 'bearer',
        bearerFormat: 'JWT',
        name: 'JWT',
        description: 'Entrer votre token JWT',
        in: 'header',
      },
      'JWT-auth',
    )
    .addApiKey(
      {
        type: 'apiKey',
        name: 'x-api-key',
        in: 'header',
        description: 'Cle API publique (separee du JWT). Voir variable PUBLIC_API_KEY dans .env',
      },
      'api-key',
    )
    .addTag('auth', 'Authentification (login, register, logout)')
    .addTag('users', 'Gestion des utilisateurs')
    .addTag('posts', 'Publications et likes')
    .addTag('comments', 'Commentaires sur les posts')
    .addTag('friends', 'Systeme d\'amis')
    .addTag('messages', 'Messagerie privee')
    .addTag('notifications', 'Notifications temps reel')
    .addTag('public-api', 'API publique protegee par cle API (x-api-key)')
    .addTag('health', 'Health checks')
    .build();

  const document = SwaggerModule.createDocument(app, swaggerConfig);
  SwaggerModule.setup('api/docs', app, document);

  // Demarrer le serveur
  const port = configService.get<number>('PORT') || 3001;
  await app.listen(port);

  console.log(`Application lancee sur: http://localhost:${port}`);
  console.log(`Documentation Swagger: http://localhost:${port}/api/docs`);
  console.log('Securite activee: Helmet, CORS strict, Rate Limiting, Security Logging');
}

bootstrap();
