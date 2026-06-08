/**
 * @responsable clfouger
 * COMPOSANT LOADER - Spinner de chargement
 */

export const Loader = ({ size = '20px' }) => {
  return (
    <div
      className="loader"
      style={{
        width: size,
        height: size,
        borderWidth: `calc(${size} / 7)`
      }}
    />
  )
}
