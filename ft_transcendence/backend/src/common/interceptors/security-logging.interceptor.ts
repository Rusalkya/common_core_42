import {
  Injectable,
  NestInterceptor,
  ExecutionContext,
  CallHandler,
  Logger,
} from '@nestjs/common';
import { Observable } from 'rxjs';
import { tap, catchError } from 'rxjs/operators';
import { throwError } from 'rxjs';

@Injectable()
export class SecurityLoggingInterceptor implements NestInterceptor {
  private readonly logger = new Logger('Security');

  intercept(context: ExecutionContext, next: CallHandler): Observable<any> {
    const req = context.switchToHttp().getRequest();
    const { method, url, ip, headers } = req;
    const userAgent = headers['user-agent'] || 'unknown';
    const userId = req.user?.id || 'anonymous';

    const sensitiveRoutes = ['/auth/login', '/auth/register', '/auth/me'];
    const isSensitive = sensitiveRoutes.some(route => url.includes(route));

    if (isSensitive) {
      this.logger.log(
        `[${method}] ${url} | IP: ${ip} | User: ${userId} | UA: ${userAgent}`
      );
    }

    return next.handle().pipe(
      tap(() => {
        if (isSensitive) {
          this.logger.log(`Success: ${method} ${url} | User: ${userId}`);
        }
      }),
      catchError((error) => {
        if (isSensitive) {
          this.logger.warn(
            `Failed: ${method} ${url} | IP: ${ip} | User: ${userId} | Error: ${error.message}`
          );
        }
        return throwError(() => error);
      }),
    );
  }
}
