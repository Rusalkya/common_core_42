/**
 * @responsable clfouger
 * COMPOSANT AVATAR - Affichage d'avatar utilisateur
 */

export const Avatar = ({ src, alt = 'Avatar', size = 'md', className = '' }) => {
  const sizeClass = `avatar-${size}`

  return (
    <div className={`avatar ${sizeClass} ${className}`}>
      {src ? (
        <img src={src} alt={alt} />
      ) : (
        <span>{alt.charAt(0).toUpperCase()}</span>
      )}
    </div>
  )
}
