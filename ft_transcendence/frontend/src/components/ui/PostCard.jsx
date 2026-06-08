/**
 * @responsable clfouger
 * COMPOSANT POST CARD - Affichage d'un dessin dans le feed
 */

import { Avatar } from './Avatar'
import { Button } from './Button'

export const PostCard = ({ 
  post, 
  onLike, 
  onComment, 
  onShare,
  isLiked = false 
}) => {
  return (
    <div className="post-card">
      {/* En-tete du post */}
      <div className="flex-between">
        <div style={{ display: 'flex', alignItems: 'center', gap: 'var(--spacing-md)' }}>
          <Avatar src={post.author.avatar} alt={post.author.username} size="md" />
          <div>
            <div style={{ fontWeight: 'var(--font-weight-bold)' }}>
              {post.author.username}
            </div>
            <div style={{ fontSize: 'var(--font-size-xs)', color: 'var(--color-text-tertiary)' }}>
              {new Date(post.createdAt).toLocaleDateString('fr-FR')}
            </div>
          </div>
        </div>
      </div>

      {/* Image du dessin */}
      {post.image && (
        <img src={post.image} alt="Dessin" className="post-image" />
      )}

      {/* Description */}
      {post.description && (
        <p style={{ marginTop: 'var(--spacing-md)', color: 'var(--color-text-primary)' }}>
          {post.description}
        </p>
      )}

      {/* Actions */}
      <div className="post-actions">
        <button className="post-action-btn" onClick={() => onLike(post.id)}>
          {isLiked ? '❤️' : '🤍'} <span>{post.likeCount || 0}</span>
        </button>
        <button className="post-action-btn" onClick={() => onComment(post.id)}>
          💬 <span>{post.commentCount || 0}</span>
        </button>
        <button className="post-action-btn" onClick={() => onShare(post.id)}>
          📤 <span>{post.shareCount || 0}</span>
        </button>
      </div>
    </div>
  )
}
